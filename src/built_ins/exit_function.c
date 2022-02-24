/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:14:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 10:52:51 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_shl_lvl(char **envp, int change)
{
	char		*shlvl;
	int			shlvl_current;
	char		*new_shlvl;

	shlvl_current = ft_atoi(ft_getenv("SHLVL", envp));
	new_shlvl = ft_itoa(shlvl_current + change);
	shlvl = ft_strjoin("SHLVL=", new_shlvl);
	free(new_shlvl);
	export_simple(shlvl, envp);
	free(shlvl);
}

static void	exit_msg_error(char *input, int fd)
{
	ft_putstr_fd("nminishell>: exit: ", fd);
	ft_putstr_fd(input, fd);
	ft_putendl_fd(": numeric argument required", fd);
}

static int	count_cmd_args(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmds[i])
		i++;
	return (i - 1);
}

bool	is_valid_exit(t_command *cmd)
{
	int		i;

	if (cmd && cmd->cmds && ft_strcmp(cmd->cmds[0], "exit"))
		return (false);
	if (!cmd || !cmd->cmds[1])
		return (true);
	i = 0;
	while (cmd->cmds[1][i])
	{
		if (!ft_isdigit(cmd->cmds[1][i]))
			return (true);
		i++;
	}
	if (count_cmd_args(cmd) > 1)
		return (false);
	return (true);
}

/*
 * exit function will exit the minishell
 * with the exit value given as argument (or 255 if non numeric argument given)
 * if there are too many arguments (more than 1) it will exit with 1.
 * still need to free the envp and input.
 * !!!checking for shl_lvl might not be necesarry!
 * the fd_out might be that it needs to be fd_error or just 1 or 2.
 */
void	exit_function(t_command *cmd, char **envp)
{
	int	i;

	if (!cmd || !cmd->cmds[1])
		exit(0);
	i = 0;
	while (cmd->cmds[1][i] && envp)
	{
		if (!ft_isdigit(cmd->cmds[1][i]))
		{
			exit_msg_error(cmd->cmds[1], cmd->fd_error);
			exit(255);
		}
		i++;
	}
	if (count_cmd_args(cmd) > 1)
	{
		ft_putendl_fd("minishell>: exit: too many arguments", cmd->fd_error);
		set_return_value(envp, 1);
		return ;
	}
	exit(ft_atoi(cmd->cmds[1]) % 255);
}
