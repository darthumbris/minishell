/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                        :+:    :+:           */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 12:11:14 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/01 17:18:08 by abba            ########   odam.nl       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <stdio.h>

int	err_msg(char *msg, int ret)
{
	perror(msg);
	return (ret);
}

void	closing_pipes(t_pipe *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->pipes)
	{
		close(pipe->fd[i][0]);
		close(pipe->fd[i][1]);
		i++;
	}
}

void	set_pipes(t_pipe *pipe_strct)
{
	int		i;

	i = 0;
	while (i < pipe_strct->pipes)
	{
		if (pipe(pipe_strct->fd[i]) == -1)
			exit(err_msg("PIPE", 1));
		i++;
	}
}

static int	**get_pipefd(int pipes)
{
	int	**fd;
	int	i;

	fd = ft_calloc(pipes, sizeof(int *));
	if (!fd)
		return (0);
	i = 0;
	while (i < pipes && fd)
	{
		fd[i] = ft_calloc(2, sizeof(int));
		if (fd[i] == NULL)
		{
			i--;
			while (i)
			{
				free(fd[i]);
				i--;
			}
			free(fd);
			return (NULL);
		}
		i++;
	}
	return (fd);
}

void	init_pipe_strct(t_pipe *pipe, int pipes)
{
	pipe->fd = get_pipefd(pipes);
	pipe->pids = ft_calloc(pipes + 1, sizeof(pid_t));
	if (!pipe->pids)
		return ;
	pipe->pipes = pipes;
}
