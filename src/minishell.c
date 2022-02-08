/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/08 10:56:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

/*
 * temporary function to check the lexer
 * functionality.
 */
t_token	*lexer_checker(char *input, char **envp)
{
	t_token		*lst;
	t_token		*tmp;

	lst = lexer(input);
	tmp = lst;
	while (tmp)
	{
		if ((tmp->token_name[0] == 'W' || tmp->token_name[0] == 'F') && \
			strchr(tmp->token_value, '$'))
			check_for_env_expansion(&(tmp->token_value), envp);
		tmp = tmp->next;
	}
	lst = quote_expansion(lst);
	tmp = lst;
	while (tmp)
	{
		printf("token_name: %s\t", tmp->token_name);
		printf("lst_value: %s\n", tmp->token_value);
		tmp = tmp->next;
	}
	evaluator(lst);
	create_cmd_lst(lst);
	return (lst);
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
 * or might be able to store it differently.
 */
int	main(int argc, char **argv, char **envp)
{
	static char		*input;
	char			**envp_dup;
	int				i;
	t_token			*lst;

	input = NULL;
	rl_catch_signals = 0;
	if (argc != 1 || !argv || !envp)
	{
		i = 1;
		while (argv[i])
			printf("argv[1]: %s\n", argv[i++]);
		//return (1);
		//not sure about this return yet.
	}
	signal(SIGINT, signal_handle_function);
	signal(SIGQUIT, signal_handle_function);
	envp_dup = envp_duplicate(envp);
	while (1)
	{
		input = get_input(input);
		if (input == NULL)
		{
			if (lst)
				free_token_lst(&lst);
			exit_function("0", envp_dup);
		}
		if (input && *input)
		{
			if (lst)
				free_token_lst(&lst);
			lst = lexer_checker(input, envp_dup);
			//parse_input(input, envp_dup);
		}
	}
	system("leaks minishell");
	return (0);
}
