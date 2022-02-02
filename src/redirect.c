/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 12:56:39 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/02 13:09:11 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	redirect_input(char *path, t_command *cmd)
{
	cmd->fd_in = open(path, O_RDONLY);
	if (cmd->fd_in < 0)
		perror(path);
}

void	redirect_output(char *path, t_command *cmd, int append)
{
	if (append)
		cmd->fd_out = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		cmd->fd_out = open(path, O_WRONLY | O_CREAT, 0644);
	if (cmd->fd_out < 0)
		perror(path);
}

// void	redirect_error(t_command *cmd, int fd)
// {
// 	cmd->fd_error = fd;
// }
