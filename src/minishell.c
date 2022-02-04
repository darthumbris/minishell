/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/04 11:53:11 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

void	lexer_checker(char *input)
{
	t_token	*lst;

	printf("checking lexer\n");
	lst = lexer(input);
	if (!lst)
		printf("lst is NULL\n");
	while (lst)
	{
		printf("token_name: %s\t", lst->token_name);
		printf("lst_value: %s\n", lst->token_value);
		lst = lst->next;
	}
	printf("done with lexing\n");
}

/*
 * This function will create the child process to handle the simple 
 * commands. Won't work yet with pipe.
 * Also the return value required for the echo $? needs to be done
 * THIS FUNCTION IS TEMPORARY UNTIL PIPE ETC IS WORKING!!!!.
 * or need to change it in case there is only one command (no pipes)
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
}

/*
 * !!!need to properly check the shlvl at
 * the start of program. Or force it to 1
 * at the beginning. not sure yet what is 
 * correct.
 * Probably have a global struct
 * with a shlvl and return value
 * and maybe some other stuff
 * that bash stores itself and in env
 */
int	main(int argc, char **argv, char **envp)
{
	static char		*input;
	char			**envp_dup;

	input = NULL;
	rl_catch_signals = 0;
	if (argc != 1 || !argv || !envp)
		return (1);
	signal(SIGINT, signal_handle_function);
	signal(SIGQUIT, signal_handle_function);
	envp_dup = envp_duplicate(envp);
	while (1)
	{
		input = get_input(input);
		if (input == NULL)
			exit_function("0", envp_dup);
		if (input && *input)
		{
			lexer_checker(input);
			//parse_input(input, envp_dup);
		}
	}
	return (0);
}
