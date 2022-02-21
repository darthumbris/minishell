/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_struct.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:05:34 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/17 15:46:06 by shoogenb      ########   odam.nl         */
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
	new->ret = 0;
	return (new);
}
