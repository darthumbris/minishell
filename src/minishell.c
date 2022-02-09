/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/09 12:49:23 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

/*
 * temporary function to check the lexer
 * functionality. and other stuff.
 */
void	lexer_checker(char *input, char **envp)
{
	t_token		*lst;
	t_token		*tmp;
	t_command	*test;

	lst = lexer_lst(input, envp);
	tmp = lst;
	lst = lst->next;
	test = create_cmd_lst(lst);
	if (test)
	{
		parse_input(test, envp);
		free_token_lst(&tmp);
		free_cmd_args(test->cmds);
		free(test);
	}
	tmp = NULL;
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
 * the start of program. Or increase it by 1
 * at the beginning. not sure yet what is 
 * correct.
 * Probably have a global struct
 * with a shlvl and return value
 * and maybe some other stuff
 * that bash stores itself and in env
 * or might be able to store it differently.
 */
int	main(int argc, char **argv, char **envp)
{
	static char		*input;
	char			**envp_dup;

	input = NULL;
	rl_catch_signals = 0;
	if (argc != 1 || !argv || !envp)
		return (1); //not sure about this return yet.
	signal(SIGINT, signal_handle_function);
	signal(SIGQUIT, signal_handle_function);
	envp_dup = envp_duplicate(envp);
	change_shl_lvl(envp_dup, 1);
	while (1)
	{
		input = get_input(input);
		if (input == NULL)
			exit_function(NULL, envp_dup);
		if (input && *input)
		{
			lexer_checker(input, envp_dup);
			//parse_input(input, envp_dup);
		}
	}
	system("leaks minishell");
	return (0);
}
