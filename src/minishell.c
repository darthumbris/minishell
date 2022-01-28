/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/01/28 10:58:43 by shoogenb      ########   odam.nl         */
=======
/*   Updated: 2022/01/27 14:58:19 by abba          ########   odam.nl         */
>>>>>>> 85e49327b055e28a6ca81df270e0541be89cd788
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
 * need to figure out how to handle the ctr-\ thing
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
		printf("ctrl-\\ \n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	static char	*input;
	char		**envp_dup;

	input = NULL;
	if (argc != 1 || !argv || !envp)
		return (1);
	signal(SIGINT, signal_handle_function);
	envp_dup = envp_duplicate(envp);
	while (1)
	{
		input = get_input(input);
		if (input == NULL)
		{
			printf("exit\n");
			system("leaks minishell");
			return (0);
		}
		if (input && *input)
		{
			//quote_parser(input);
			parse_input(input, envp_dup);
		}
	}
	return (0);
}
