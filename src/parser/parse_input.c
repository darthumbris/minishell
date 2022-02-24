/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 10:56:33 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 16:34:22 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_count(t_command **cmds)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (cmds[i])
			i++;
	}
	return (i);
}

static void	parse_input_child(int cmd_cnt, t_command **cmds, char **envp)
{
	if (cmd_cnt > 1)
	{
		pipex(cmds, envp, cmd_cnt - 1);
		exit(1);
	}
	else if (cmd_cnt == 1)
	{
		redirect(cmds[0], 0);
		parse_command(cmds[0], envp);
	}
}

static void	parse_input_parent(int pid, char **envp)
{
	int	status;

	status = 0;
	disable_signals();
	waitpid(pid, &status, 0);
	if (status == 3)
		signal_handle_function(SIGQUIT);
	if (status == 2)
		signal_handle_function(SIGINT);
	set_return_value(envp, WEXITSTATUS(status));
}

void	parse_input(char *input, char **envp)
{
	t_token		*lst;
	t_command	**cmds;
	pid_t		pid;
	int			cmd_cnt;

	lst = lexer_lst(input, envp);
	cmds = get_commands(lst, count_pipes(lst, envp) + 1, envp);
	cmd_cnt = get_cmd_count(cmds);
	if (cmd_cnt == 1 && is_valid_exit(cmds[0]))
		parse_command(cmds[0], envp); //might need to handle heredoc
	if (cmd_cnt)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("FORK");
			return (set_return_value(envp, 1));
		}
		if (pid == 0)
			parse_input_child(cmd_cnt, cmds, envp);
		else
			parse_input_parent(pid, envp);
	}
	free_cmd_lst(cmds);
	free_token_lst(&lst);
}
