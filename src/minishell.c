/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/25 16:12:33 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function will create the child process to handle the simple 
 * commands. Won't work yet with pipe.
 * Also the return value required for the echo $? needs to be done
 */
int	minishell_thing(char *input, char **envp)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("FORK: ");
		return (1);
	}
	if (child_pid == 0)
		execute_input(input, envp);
	waitpid(child_pid, &status, 0);
	return (WEXITSTATUS(status));
}

/*
 * This function handles the ctrl-c for now
 * it will make a new line and clear the input.
 */
void	signal_handle_function(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		printf("ctrl-c \n");
	}
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
			system("leaks minishell");
			exit(0);
		}
		if (input && *input)
			minishell_thing(input, envp);
	}
	return (0);
}
