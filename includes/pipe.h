/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 10:23:58 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 12:17:40 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_pipe
{
	int		pipes;
	int		**fd;
	pid_t	*pids;
}				t_pipe;

void	set_pipes(t_pipe *pipe_strct);
void	closing_pipes(t_pipe *pipe);
void	init_pipe_strct(t_pipe *pipe, int pipes);
int		err_msg(char *msg, int ret);

#endif