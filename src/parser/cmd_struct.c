/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_struct.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:05:34 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 10:51:03 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(cmd);
	cmd = NULL;
}

void	free_cmd_lst(t_command **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free_cmds(cmds[i]);
		i++;
	}
	free(cmds);
}
