/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 10:49:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/21 16:27:10 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(char *msg, int ret)
{
	perror(msg);
	return (ret);
}

int	new_pipex_multiple(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		err_msg("FORK", 1);
	else if (pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		dup_and_close(&(cmd->fd_out), STDOUT_FILENO);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		//close(pipe_fd[0]);
		waitpid(pid, &status, 0);
	}
	else
	{
		dup_and_close(&(cmd->fd_in), STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		//close(pipe_fd[1]);
		parse_command(cmd, envp);
	}
	set_return_value(envp, WEXITSTATUS(status));
	return (status);
}

static int	count_cmd_args_lst(t_token *lst)
{
	t_token	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		if (tmp->token_name[0] == '|')
			break ;
		if (tmp->token_name[0] == 'W')
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_command	*get_next_command(t_token **lst, char **envp)
{
	char		**cmds;
	int			len;
	int			i;
	t_command	*cmd;

	while ((*lst))
	{
		if ((*lst)->token_name[0] == 'W')
		{
			cmd = new_command(NULL);
			len = count_cmd_args_lst((*lst));
			cmds = ft_calloc(len + 1, sizeof(char *));
			i = 0;
			while (i < len)
			{
				if ((*lst)->token_name[0] == 'W')
					cmds[i++] = ft_strdup((*lst)->token_value);
				if ((*lst)->token_name[0] == '>' && cmd->fd_out != -1)
				{
					dup_and_close(&(cmd->fd_out), STDOUT_FILENO);
					cmd->fd_out = redirect_parse((*lst), envp);
				}
				else if (((*lst)->token_name[0] == '<' || (*lst)->token_name[0] == 'h') && cmd->fd_in != -1)
				{
					dup_and_close(&(cmd->fd_in), STDIN_FILENO);
					cmd->fd_in = redirect_parse((*lst), envp);
				}
				(*lst) = (*lst)->next;
			}
			cmd->cmds = cmds;
			return (cmd);
		}
		if ((*lst))
			(*lst) = (*lst)->next;
	}
	return (NULL);
}

t_command	**get_commands(t_token *lst, t_command *cmd, int cmd_cnt, char **envp)
{
	t_command	**cmds;
	t_token		*tmp;
	int			i;

	tmp = lst;
	cmds = ft_calloc(cmd_cnt + 1, sizeof(t_command *));
	i = 0;
	while (i < cmd_cnt)
	{
		cmds[i] = get_next_command(&tmp, envp);
		check_redir_in(&tmp, envp, cmds[i]);
		check_redir_out(&tmp, envp, cmds[i]);
		i++;
	}
	cmds[i] = NULL;
	if (cmd_cnt == 1 && !cmds[0])
	{
		tmp = lst;
		while (tmp)
		{
			check_redir_in(&tmp, envp, cmd);
			check_redir_out(&tmp, envp, cmd);
			if (tmp)
				tmp = tmp->next;
		}
	}
	return (cmds);
}
