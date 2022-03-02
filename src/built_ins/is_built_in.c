/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_built_in.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 09:50:18 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/02 10:14:10 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dispatch.h"

bool	is_built_in(t_command *cmd)
{
	int			i;
	const char	*built_ins[8] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset",
		NULL
	};

	i = 0;
	while (built_ins[i])
	{
		if (cmd && cmd->cmds && ft_strcmp(cmd->cmds[0], built_ins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
