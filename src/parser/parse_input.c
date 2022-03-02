/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 10:56:33 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/02 12:29:20 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "pipe.h"
#include "heredoc.h"
#include "redirect.h"
#include "built_in.h"

static int	count_pipes(t_token *lst, char **envp)
{
	t_token		*tmp;
	int			pipe_cnt;

	tmp = lst;
	pipe_cnt = 0;
	while (tmp && envp)
	{
		if (tmp->token_name[0] == '|')
			pipe_cnt++;
		if (tmp)
			tmp = tmp->next;
	}
	return (pipe_cnt);
}

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

static void	parse_input_child(t_command **cmds, char **envp, \
							t_token *lst, int cmd_cnt)
{
	disable_signals();
	if (cmd_cnt > 1)
	{
		pipex(cmds, envp, cmd_cnt - 1);
		exit(1);
	}
	else if (cmd_cnt == 1)
	{
		if (cmds[0]->heredocs)
			heredoc_with_command(cmds[0], envp);
		redirect(cmds[0], 0);
		parse_command(cmds[0], envp, true);
	}
	else
	{
		heredoc_function(lst, envp);
		exit(0);
	}
}

static void	parse_input_parent(int pid, char **envp, \
								t_command **cmds, int cmd_cnt)
{
	int				status;
	struct termios	term_save;

	disable_signals();
	status = 0;
	if ((cmd_cnt == 1 && cmds[0]->heredocs) || !cmd_cnt)
	{
		tcgetattr(0, &term_save);
		g_pid = pid;
		signal(SIGINT, signal_heredoc);
	}
	waitpid(pid, &status, 0);
	if (status == 3 || status == 2)
		signal_handle_function(status);
	if (status == 9)
	{
		tcsetattr(0, TCSAFLUSH, &term_save);
		set_return_value(envp, 1);
		return ;
	}
	if (cmd_cnt == 1 && WIFEXITED(status) && is_valid_exit(cmds[0]))
		exit(WEXITSTATUS(status));
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
	if (cmd_cnt == 1 && is_built_in(cmds[0]) && cmds[0]->heredocs == 0)
		parse_command(cmds[0], envp, false);
	else if (cmds && lst && cmds[0]->cmds && cmds[0]->cmds[0])
	{
		pid = fork();
		if (pid < 0)
		{
			perror("FORK");
			return (set_return_value(envp, 1));
		}
		if (pid == 0)
			parse_input_child(cmds, envp, lst, cmd_cnt);
		else
			parse_input_parent(pid, envp, cmds, cmd_cnt);
	}
	free_cmd_lst(cmds);
	free_token_lst(&lst);
}
