/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/21 16:57:20 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

/*
 * This function handles the ctrl-c for now
 * it will make a new line and clear the input.
 * need to figure out how to handle the ctr-\ thing
 * also do something different when in a functin/command
 * and with just normal input should do the replace stuff
 */
void	signal_handle_function(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

void	signal_handle_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	parse_input_new(char *input, char **envp)
{
	t_token		*lst;
	int			pipe_cnt;
	t_command	**cmds;
	t_command	*cmd;

	if (input && *input)
	{
		lst = lexer_lst(input, envp);
		check_valid_commands(lst, envp);
		pipe_cnt = count_pipes(lst, envp);
		cmd = new_command(NULL);
		cmds = get_commands(lst, cmd, pipe_cnt + 1, envp);
		printf("now do something with this???\n");
	}
}

void	parse_input(char *input, char **envp)
{
	t_token		*lst;
	pid_t		pid;
	int			status;
	t_command	*exit_cmd;

	if (input && *input)
	{
		lst = lexer_lst(input, envp);
		check_valid_commands(lst, envp); //probably not needed.
		exit_cmd = get_exit_cmd(lst);
		pid = fork();
		if (pid < 0)
		{
			perror("FORK");
			ft_putendl_fd("error", 2);
			return ;
		}
		if (pid)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
		}
		else if (pid == 0 && !exit_cmd)
			parse_token_lst(lst, envp);
		if (lst)
			free_token_lst(&lst);
		if (exit_cmd && pid == 0)
		{
			parse_command(exit_cmd, envp);
			free_cmds(exit_cmd);
		}
		set_return_value(envp, WEXITSTATUS(status));
		if (WIFEXITED(status) == 0 && status == 3 && WEXITSTATUS(status) != 127)
			signal_handle_function(SIGQUIT);
		else if (WIFEXITED(status) == 0 && status == 2)
			signal_handle_function(SIGINT);
		if (exit_cmd && is_valid_exit(exit_cmd))
		{
			ft_putendl_fd("exit", 2);
			exit(ft_atoi(envp[0]));
		}
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
	//int				status;

	input = NULL;
	rl_catch_signals = 0;
	if (argc != 1 || !argv || !envp)
		return (1); //not sure about this return yet.
	signal(SIGINT, signal_handle_child);
	signal(SIGQUIT, signal_handle_child);
	envp_dup = envp_duplicate(envp);
	change_shl_lvl(envp_dup, 1);
	while (1)
	{
		signal(SIGINT, signal_handle_child);
		signal(SIGQUIT, signal_handle_child);
		input = get_input(input);
		if (input == NULL)
		{
			ft_putstr_fd("\x1b[1Aminishell> ", 1);
			ft_putendl_fd("exit", 2);
			exit(0);
		}
		if (input && *input)
		{
			parse_input_new(input, envp_dup);
			//waitpid(0, &status, 0);
		}
	}
	return (0);
}
