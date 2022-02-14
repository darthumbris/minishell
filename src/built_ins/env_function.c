/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_function.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:12:01 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/11 10:57:10 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_putendl_fd(envp[i], cmd->fd_out);
			i++;
		}
		set_return_value(envp, 0);
	}
}
