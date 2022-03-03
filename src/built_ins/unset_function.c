/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_function.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 13:37:34 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/03 12:25:52 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	identifier_msg(char *input, char *cmd, int fd)
{
	ft_putstr_fd("minishell>: ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(" : `", fd);
	ft_putstr_fd(input, fd);
	ft_putendl_fd("\': not a valid identifier", fd);
}

static void	check_for_var_unset(char **envp, t_command *cmd, int i, int j)
{
	if (ft_strncmp(envp[i], cmd->cmds[j], ft_strlen(cmd->cmds[j])) == 0)
	{
		free(envp[i]);
		while (envp[i + 1])
		{
			envp[i] = envp[i + 1];
			i++;
		}
		envp[i] = NULL;
	}
}

/*
 * The unset function the same as the export function
 * should accept multiple arguments to unset.
 */
void	unset_function(t_command *cmd, char **envp)
{
	int		i;
	int		j;
	int		error;

	j = 1;
	error = 0;
	while (cmd->cmds[j])
	{
		if (!is_valid_var_name(cmd->cmds[j]) || !ft_getenv(cmd->cmds[j], envp))
		{
			identifier_msg(cmd->cmds[j], cmd->cmds[0], cmd->fd_out);
			error = 1;
			j++;
		}
		i = 2;
		while (envp[i] && cmd->cmds[j])
		{
			check_for_var_unset(envp, cmd, i, j);
			i++;
		}
		if (cmd->cmds[j])
			j++;
	}
	set_return_value(envp, error);
}
