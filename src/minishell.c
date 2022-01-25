/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/25 10:04:35 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_str(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 5))
			return (ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i])), ':'));
		i++;
	}
	return (NULL);
}

char	**get_cmd_arg(char *argv)
{
	char	**cmd_args;

	cmd_args = ft_split(argv, ' ');
	return (cmd_args);
}

/*
 * The Access check is there to check if the command is actually
 * an executable file.
 * It will loop through all the paths in the envp to look
 * for the command to execute.
 */
void	command_exec(char **paths, char **cmd_args, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*cmd_slash;

	i = 0;
	cmd_slash = ft_strjoin("/", cmd_args[0]);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd_slash);
		if (!access(cmd_path, 0))
			execve(cmd_path, cmd_args, envp);
		free(cmd_path);
		i++;
	}
	free(cmd_slash);
}

void	free_cmd_args(char **cmd_args)
{
	int	i;

	i = 0;
	if (cmd_args)
	{
		while (cmd_args[i])
		{
			free(cmd_args[i]);
			i++;
		}
		free(cmd_args);
	}
}

void	check_input(char *input, char **envp)
{
	char	**paths;
	char	**cmd_args;

	paths = get_path_str(envp);
	cmd_args = get_cmd_arg(input);
	command_exec(paths, cmd_args, envp);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_cmd_args(cmd_args);
	exit(127);
}

void	minishell_thing(char *input, char **envp)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid < 0)
		return (perror("FORK: "));
	if (child_pid == 0)
		check_input(input, envp);
	waitpid(child_pid, &status, 0);
	//exit(WEXITSTATUS(status));
}

void signal_handle_function(int sig)
{
	if (sig == 2)
		exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc != 1 || !argv || !envp)
		return (1);
	signal(SIGINT, signal_handle_function);
	while (1)
	{
		input = readline("");
		if (!input)
			exit(0);
		minishell_thing(input, envp);
	}
	return (0);
}
