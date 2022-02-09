/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_function.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 13:36:42 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/09 13:13:32 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * the pwd function just needs to handle the pwd
 * it doesn't need any arguments. (and won't complain if there are any in bash)
 * I think?
 */
void	pwd_function(t_command *cmd, char **envp)
{
	char	*pwd_str;

	if (cmd->cmds && envp)
	{
		pwd_str = getcwd(NULL, -1);
		if (!pwd_str)
			ft_putendl_fd(ft_getenv("PWD", envp), cmd->fd_out);
		else
		{
			ft_putendl_fd(pwd_str, cmd->fd_out);
			free(pwd_str);
		}
		set_return_value(envp, 0);
	}
}
