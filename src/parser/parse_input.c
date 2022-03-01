/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 10:56:33 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/01 12:00:54 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	parse_input_child(int cmd_cnt, t_command **cmds, char **envp)
{
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
		parse_command(cmds[0], envp);
	}
}

static void	parse_input_parent(int pid, char **envp, t_command **cmds, \
							int cmd_cnt)
{
	int				status;
	struct termios	term_save;

	status = 0;
	disable_signals();
	if (cmd_cnt == 1 && cmds[0]->heredocs)
	{
		tcgetattr(0, &term_save);
		g_pid = pid;
		signal(SIGINT, signal_heredoc);
	}
	waitpid(pid, &status, 0);
	if (status == 3)
		signal_handle_function(SIGQUIT);
	if (status == 2)
		signal_handle_function(SIGINT);
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
			parse_input_parent(pid, envp, cmds, cmd_cnt);
	}
	else
		heredoc_function(lst, envp);
	free_cmd_lst(cmds);
	free_token_lst(&lst);
}
