/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_struct.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:05:34 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/07 10:29:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_command	*new_command(char **cmds)
{
	t_command	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->cmds = cmds;
	new->fd_error = 2;
	new->fd_in = 0;
	new->fd_out = 1;
	new->delimiter = NULL;
	new->heredocs = 0;
	return (new);
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
	if (cmd->delimiter)
	{
		i = 0;
		while (cmd->delimiter[i])
		{
			free(cmd->delimiter[i]);
			i++;
		}
		free(cmd->delimiter);
	}
	free(cmd);
	cmd = NULL;
}

void	free_cmd_args(char **cmd_args)
{
	int	i;

	i = 0;
	if (cmd_args)
	{
		while (cmd_args[i])
		{
			free(cmd_args[i]);
			i++;
		}
		free(cmd_args);
	}
	cmd_args = NULL;
}

void	free_cmd_lst(t_command ***cmds)
{
	int	i;

	i = 0;
	if (!(*cmds))
		return ;
	while ((*cmds)[i])
	{
		if ((*cmds)[i]->fd_out > 2)
			close((*cmds)[i]->fd_out);
		if ((*cmds)[i]->fd_in > 2)
			close((*cmds)[i]->fd_in);
		free_cmds((*cmds)[i]);
		i++;
	}
	free((*cmds));
	(*cmds) = NULL;
}
