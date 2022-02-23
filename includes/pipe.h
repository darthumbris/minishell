/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 10:23:58 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/23 12:01:48 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

typedef struct s_pipe
{
	int		pipe_io1[2];
	int		pipe_io2[2];
	int		kind;
	bool	change;
	int		pipes;
	int		cur_pipe[2];
	int		prev_pipe[2];
	int		temp_fd[2];
	int		**fd;
	pid_t	*pid;
	int		i;
	int		pipes_static;
}				t_pipe;

#endif