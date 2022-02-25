/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 11:04:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/25 11:49:11 by shoogenb      ########   odam.nl         */
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

static void	set_current_command(t_command *cmd, t_token **lst, \
								char **envp, int len)
{
	char		**cmds;
	int			i;

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
		else if ((*lst)->token_name[0] == '<' && cmd->fd_in != -1)
		{
			dup_and_close(&(cmd->fd_in), STDIN_FILENO);
			cmd->fd_in = redirect_parse((*lst), envp);
		}
		else if ((*lst)->token_name[0] == 'h' && !(cmd->delimiter))
		{
			cmd->delimiter = get_delimiter(*lst);
			cmd->fd_in = 0;
		}
		(*lst) = (*lst)->next;
	}
	cmd->cmds = cmds;
}

static t_command	*get_next_command(t_token **lst, char **envp, \
									int fd_in, int fd_out)
{
	t_command	*cmd;
	char		**delimiter;

	delimiter = NULL;
	while ((*lst))
	{
		if ((*lst)->token_name[0] == '>')
			fd_out = redirect_parse((*lst), envp);
		if ((*lst)->token_name[0] == '<')
			fd_in = redirect_parse((*lst), envp);
		if ((*lst)->token_name[0] == 'h' && !delimiter)
		{
			delimiter = get_delimiter((*lst));
			fd_in = 0;
		}
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
	return (NULL);
}

//Might need to change it so it stores the heredoc delimters in the cmd
//and if there are no commands than check the token lst for heredocs and do
//them then.
t_command	**get_commands(t_token *lst, int cmd_cnt, char **envp)
{
	t_command	**cmds;
	t_token		*tmp;
	int			i;

	if (!lst)
		return (NULL);
	tmp = lst;
	cmds = ft_calloc(cmd_cnt + 1, sizeof(t_command *));
	i = 0;
	while (i < cmd_cnt)
	{
		cmds[i] = get_next_command(&tmp, envp, 0, 1);
		check_redir_in(&tmp, envp, cmds[i]);
		check_redir_out(&tmp, envp, cmds[i]);
		if (check_heredoc(&tmp, cmds[i]))
			cmds[i]->fd_in = 0;
		if (cmds[i] && cmds[i]->delimiter)
		{
			while (cmds[i]->delimiter[cmds[i]->heredocs])
				cmds[i]->heredocs++;
		}
		i++;
	}
	return (cmds);
}
