/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_function.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:12:01 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/04 10:52:07 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

/*
 * This function checks if the input
 * has an equal sign. 
 * because the env doesn't show it then
 * but the export function does.
 */
static bool	has_equals(char *input)
{
	if (ft_strchr(input, '='))
		return (true);
	return (false);
}

/*
 * The env doesn't need to accept any options or arguments.
 * it will just print the env no matter what
 * (in bash the argument needs to be an env variable and it will
 * print only the value of that variable I think)
 */
void	env_function(t_command *cmd, char **envp)
{
	int	i;

	if (cmd && envp && cmd->cmds)
	{
		i = 2;
		while (envp[i])
		{
			if (has_equals(envp[i]))
				ft_putendl_fd(envp[i], cmd->fd_out);
			i++;
		}
		set_return_value(envp, 0);
	}
}
