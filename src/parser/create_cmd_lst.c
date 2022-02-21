/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd_lst.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 14:28:29 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/21 14:54:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function will check
 * how big the cmd args are
 * for the cmd struct.
 */
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
		if (tmp)
			tmp = tmp->next;
	}
	return (count);
}

void	free_cmds(t_command *cmd)
{
	int	i;

	if (cmd->cmds)
	{
		i = 0;
		while (cmd->cmds[i])
		{
			free(cmd->cmds[i]);
			i++;
		}
		free(cmd->cmds);
	}
	free(cmd);
	cmd = NULL;
}

void	close_fd_cmd(t_command *cmd)
{
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		ft_putendl_fd("closing out3", 2);
		close(cmd->fd_out);
		cmd->fd_out = 1;
	}
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		ft_putendl_fd("closing in3", 2);
		close(cmd->fd_in);
		cmd->fd_in = 0;
	}
}

/*
 * This function will create a command struct
 * using the token list. Basically
 * a word token will be converted to a command
 * if there are multiple word tokens
 * after each other they will be converted
 * to a cmd_arg array
 * where cmd_arg[0] is the command
 * and all the others in the array
 * are the arguments or options.
 */
t_command	*create_cmd_lst(t_token **lst, t_command *cmd, char **envp)
{
	char		**cmds;
	int			len;
	int			i;

	if ((*lst)->token_name[0] == 'W')
	{
		len = count_cmd_args_lst((*lst));
		cmds = ft_calloc(len + 1, sizeof(char *));
		i = 0;
		while (i < len)
		{
			if ((*lst)->token_name[0] == 'W')
				cmds[i++] = ft_strdup((*lst)->token_value);
			if ((*lst)->token_name[0] == '>' && cmd->fd_out != -1)
			{
				ft_putendl_fd("hello", 2);
				if (cmd->fd_out != 1)
				{
					dup2(cmd->fd_out, STDOUT_FILENO);
					close(cmd->fd_out);
					cmd->fd_out = 1;
				}
				cmd->fd_out = redirect_parse((*lst), envp);
			}
			else if (((*lst)->token_name[0] == '<' || (*lst)->token_name[0] == 'h') && cmd->fd_in != -1)
			{
				//ft_putendl_fd("there", 2);
				if (cmd->fd_in != 0)
				{
					ft_putendl_fd("\n\n\nclosing fdin\n\n\n", 2);
					dup2(cmd->fd_in, STDIN_FILENO);
					close(cmd->fd_in);
					cmd->fd_in = 0;
				}
				cmd->fd_in = redirect_parse((*lst), envp);
			}
			(*lst) = (*lst)->next;
		}
		cmd->cmds = cmds;
		return (cmd);
	}
	return (NULL);
}
