/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 11:04:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/07 10:27:29 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"
#include "heredoc.h"

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

static void	set_current_command(t_command *cmd, t_token **lst, \
								char **envp, int len)
{
	char		**cmds;
	int			i;

	cmds = ft_calloc(len + 1, sizeof(char *));
	if (!cmds)
		return ;
	i = 0;
	while (i < len && cmds && (*lst))
	{
		if ((*lst)->token_name[0] == 'W' && (*lst)->token_value)
			cmds[i++] = ft_strdup((*lst)->token_value);
		if ((*lst)->token_name[0] == '>' && cmd->fd_out != -1)
			cmd->fd_out = redirect_parse((*lst), envp, cmd->fd_out);
		else if ((*lst)->token_name[0] == '<' && cmd->fd_in != -1)
			cmd->fd_in = redirect_parse((*lst), envp, cmd->fd_in);
		else if ((*lst)->token_name[0] == 'h' && !(cmd->delimiter))
		{
			cmd->delimiter = get_delimiter(*lst);
			cmd->fd_in = 0;
		}
		if ((*lst))
			(*lst) = (*lst)->next;
	}
	cmd->cmds = cmds;
}

static char	**check_redirect_command(t_token **lst, char **envp, \
									int *fd_in, char **delimiter)
{
	if ((*lst)->token_name[0] == '<' && *fd_in >= 0)
		*fd_in = redirect_parse((*lst), envp, *fd_in);
	if ((*lst)->token_name[0] == 'h' && !delimiter)
	{
		delimiter = get_delimiter((*lst));
		*fd_in = 0;
	}
	return (delimiter);
}

static t_command	*get_next_command(t_token **lst, char **envp, \
									int fd_in, int fd_out)
{
	t_command	*cmd;
	char		**delimiter;

	delimiter = NULL;
	while ((*lst))
	{
		delimiter = check_redirect_command(lst, envp, &fd_in, delimiter);
		if ((*lst)->token_name[0] == '>' && fd_out > 0)
			fd_out = redirect_parse((*lst), envp, fd_out);
		if ((*lst)->token_name[0] == 'W')
		{
			cmd = new_command(NULL);
			cmd->fd_in = fd_in;
			cmd->fd_out = fd_out;
			cmd->delimiter = delimiter;
			set_current_command(cmd, lst, envp, count_cmd_args_lst((*lst)));
			return (cmd);
		}
		if ((*lst))
			(*lst) = (*lst)->next;
	}
	if (delimiter)
		free_delimiter(delimiter);
	close_fdio(fd_in, fd_out);
	return (NULL);
}

t_command	**get_commands(t_token *lst, int cmd_cnt, char **envp)
{
	t_command	**cmds;
	t_token		*tmp;
	int			i;

	tmp = lst;
	cmds = ft_calloc(cmd_cnt + 1, sizeof(t_command *));
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < cmd_cnt && cmds)
	{
		cmds[i] = get_next_command(&tmp, envp, 0, 1);
		check_redir_in(&tmp, envp, cmds[i]);
		check_redir_out(&tmp, envp, cmds[i]);
		if (cmds[i] && (cmds[i]->fd_in < 0 || cmds[i]->fd_out < 0))
			free_cmd_lst(&cmds);
		if (cmds && check_heredoc(&tmp, cmds[i]))
			cmds[i]->fd_in = 0;
		if (cmds && cmds[i] && cmds[i]->delimiter)
			while (cmds[i]->delimiter[cmds[i]->heredocs])
				cmds[i]->heredocs++;
		i++;
	}
	return (cmds);
}
