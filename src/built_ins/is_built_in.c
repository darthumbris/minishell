/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_built_in.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 09:50:18 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/03 14:13:12 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

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
		if (cmd && cmd->cmds && cmd->cmds[0] && \
			ft_strcmp(cmd->cmds[0], built_ins[i]) == 0)
		{
			if (i == 3)
				ft_putendl_fd("exit", 2);
			return (true);
		}
		i++;
	}
	return (false);
}
