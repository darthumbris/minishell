/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 13:41:02 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/01 15:37:53 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function will give the absolute path back
 * needed to execute things. (might not be needed)
 * can be replaced with getenv("PATH=", envp)!!!
 */
static char	**path_input(char *input)
{
	char	**paths;

	paths = ft_calloc(2, sizeof(char *));
	if (!paths)
		return (NULL);
	paths[0] = ft_substr(input, 0, ft_strchr(input + 1, '/') - input);
	return (paths);
}

/*
 * This function will get all the paths
 * located in the envp variable
 */
static char	**get_path_str(char **envp)
{
	if (envp)
	{
		if (ft_getenv("PATH", envp))
			return (ft_split(ft_getenv("PATH", envp), ':'));
	}
	return (NULL);
}

/*
 * The Access check is there to check if the command is actually
 * an executable file.
 * It will loop through all the paths in the envp to look
 * for the command to execute.
 */
static void	command_exec(char **paths, char **cmd_args, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*cmd_slash;

	i = 0;
	if (cmd_args)
		cmd_slash = ft_strjoin("/", cmd_args[0]);
	else
		cmd_slash = ft_strdup("");
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
	cmd_args = NULL;
}

/*
 * 
 */
void	execute_input(t_command *cmd, char **envp)
{
	char	**paths;
	char	*input;

	input = cmd->cmds[0];
	if (input && (*input == '/' || (*input == '.' && input[1] == '/')))
		paths = path_input(input);
	else
		paths = get_path_str(envp);
	command_exec(paths, cmd->cmds, envp);
	ft_putstr_fd("minishell: ", cmd->fd_error);
	ft_putstr_fd(cmd->cmds[0], cmd->fd_error);
	ft_putendl_fd(": command not found", cmd->fd_error);
	exit(127);
}
