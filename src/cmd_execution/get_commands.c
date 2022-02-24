/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 11:04:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 13:55:36 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	set_current_command(t_command *cmd, t_token **lst, char **envp)
{
	char		**cmds;
	int			len;
	int			i;

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
		else if (((*lst)->token_name[0] == '<' || \
		(*lst)->token_name[0] == 'h') && cmd->fd_in != -1)
		{
			dup_and_close(&(cmd->fd_in), STDIN_FILENO);
			cmd->fd_in = redirect_parse((*lst), envp);
		}
		(*lst) = (*lst)->next;
	}
	cmd->cmds = cmds;
}

static t_command	*get_next_command(t_token **lst, char **envp, \
	int fd_in, int fd_out)
{
	t_command	*cmd;

	while ((*lst))
	{
		if ((*lst)->token_name[0] == '>')
			fd_out = redirect_parse((*lst), envp);
		if (((*lst)->token_name[0] == '<' || (*lst)->token_name[0] == 'h'))
			fd_in = redirect_parse((*lst), envp);
		if ((*lst)->token_name[0] == 'W')
		{
			cmd = new_command(NULL);
			cmd->fd_in = fd_in;
			cmd->fd_out = fd_out;
			set_current_command(cmd, lst, envp);
			return (cmd);
		}
		if ((*lst))
			(*lst) = (*lst)->next;
	}
	return (NULL);
}

t_command	**get_commands(t_token *lst, int cmd_cnt, char **envp)
{
	t_command	**cmds;
	t_token		*tmp;
	int			i;

	tmp = lst;
	cmds = ft_calloc(cmd_cnt + 1, sizeof(t_command *));
	i = 0;
	while (i < cmd_cnt)
	{
		cmds[i] = get_next_command(&tmp, envp, 0, 1);
		check_redir_in(&tmp, envp, cmds[i]);
		check_redir_out(&tmp, envp, cmds[i]);
		i++;
	}
	return (cmds);
}
