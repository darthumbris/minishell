/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 12:11:07 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/09 11:54:55 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_n_option(char *input)
{
	int	i;

	i = 1;
	if (input[0] == '-' && input[1] == 'n')
	{
		while (input[i] == 'n' && input[i])
			i++;
		if (input[i] == '\0')
			return (true);
	}
	return (false);
}

static void	echo_write(t_command *cmd, int i)
{
	while (cmd->cmds[i])
	{
		ft_putstr_fd(cmd->cmds[i], cmd->fd_out);
		if (cmd->cmds[i + 1])
			write(cmd->fd_out, " ", 1);
		i++;
	}
}

/*
 * echo command should check for the -n option
 * and than just print all the arguments
 * (-nnnnnn is also valid option or -nn -nn too)
 * echo will print a space between each argument:
 * echo asdf      fasdf (will print asdf fasdf)
 */
void	echo_function(t_command *cmd, char **envp)
{
	int	i;

	if (!envp)
		ft_putendl_fd("Error no envp", 2);
	if (check_n_option(cmd->cmds[1]))
	{
		i = 2;
		while (cmd->cmds[i] && check_n_option(cmd->cmds[i]))
			i++;
		echo_write(cmd, i);
	}
	else
	{
		i = 1;
		echo_write(cmd, i);
		write(cmd->fd_out, "\n", 1);
	}		
}
