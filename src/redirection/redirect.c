/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 12:56:39 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/07 10:15:47 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

/*
 * This function will open the file for input and set the 
 * fds for the cmd struct.
 * it will also give an error if the filedescriptor
 * is bad.
 */
void	redirect_input(char *path, t_command *cmd)
{
	cmd->fd_in = open(path, O_RDONLY);
	if (cmd->fd_in < 0)
		perror(path);
}

/*
 * This function will open the file for output and set the 
 * fds for the cmd struct.
 * it will also give an error if the filedescriptor
 * is bad.
 */
void	redirect_output(char *path, t_command *cmd, int append)
{
	if (append)
		cmd->fd_out = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		cmd->fd_out = open(path, O_WRONLY | O_CREAT, 0644);
	if (cmd->fd_out < 0)
		perror(path);
}

/*
 * This function will check the [n]> and [n]<
 * redirections for the n value if it is a valid
 * fd to redirect.
 */
void	redirect_fd(char *red,	t_command *cmd)
{
	if (!ft_isdigit(red[0]))
		return ;
	if (ft_atol(red) > INT_MAX)
		return (printf("minishell: file descriptor out of range: \
	 		Bad file descriptor\n"));
	else if (ft_atoi(red) > 255)
		return (printf("minishell: %d Bad file descriptor\n", \
			ft_atoi(red)));
	else if (fstat(ft_atoi(red), NULL) == -1)
		return (printf("minishell: %d Bad file descriptor\n", \
			ft_atoi(red)));
	//set fd here ?
}
