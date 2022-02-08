/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:14:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/08 16:02:30 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

//Function might be unnecesary if the cmd_exec etc. works correctly.
//or might be necesarry for when minishell is launched it 
//should increase the shlvl?
static void	change_shl_lvl(char **envp, int change)
{
	char		*shlvl;
	int			shlvl_current;
	char		*new_shlvl;

	shlvl_current = ft_atoi(ft_getenv("SHLVL", envp));
	new_shlvl = ft_itoa(shlvl_current + change);
	shlvl = ft_strjoin("SHLVL=", new_shlvl);
	free(new_shlvl);
	export_simple(shlvl, envp);
}

static void	exit_msg_error(char *input, int fd)
{
	ft_putendl_fd("exit", fd);
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
	{
		system("leaks minishell");
		exit(0);
	}
	if (count_cmd_args(cmd) > 1)
	{
		ft_putendl_fd("minishell>: exit: too many arguments", cmd->fd_out);
		//return (1);
	}
	i = 0;
	while (cmd->cmds[1][i] && envp)
	{
		if (!ft_isdigit(cmd->cmds[1][i]))
		{
			exit_msg_error(cmd->cmds[1], cmd->fd_out);
			if (ft_atoi(ft_getenv("SHLVL", envp)) == 1)
				exit(255);
			change_shl_lvl(envp, -1);
		}
		i++;
	}
	ft_putendl_fd("exit", cmd->fd_out);
	if (!ft_getenv("SHLVL", envp) || ft_atoi(ft_getenv("SHLVL", envp)) == 1)
	{
		system("leaks minishell");
		exit(ft_atoi(cmd->cmds[1]) % 255);
	}
	change_shl_lvl(envp, -1);
}
