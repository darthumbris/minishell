/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/25 13:42:49 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	signal_handle_function(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*get_input(char *input)
{
	if (input)
	{
		free(input);
		input = NULL;
	}
	input = readline("minishell> ");
	if (input && *input)
		add_history(input);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	static char	*input;

	input = NULL;
	if (argc != 1 || !argv || !envp)
		return (1);
	signal(SIGINT, signal_handle_function);
	while (1)
	{
		input = get_input(input);
		if (input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (input && *input)
			minishell_thing(input, envp);
	}
	return (0);
}
