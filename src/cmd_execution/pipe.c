/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 10:49:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 12:25:30 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipe.h"

static void	pipex_child(int i, t_pipe *pipe, t_command **cmds, char **envp)
{
	if (i == 0)
		dup2(pipe->fd[i][1], STDOUT_FILENO);
	if (i != 0 && i != pipe->pipes)
	{
		dup2(pipe->fd[i - 1][0], STDIN_FILENO);
		dup2(pipe->fd[i][1], STDOUT_FILENO);
	}
	if (i == pipe->pipes)
		dup2(pipe->fd[i - 1][0], STDIN_FILENO);
	closing_pipes(pipe);
	if (!cmds[i])
		exit(1);
	redirect(cmds[i], 0);
	parse_command(cmds[i], envp);
	exit(1);
}

static void	pipex_parent(int i, t_pipe *pipe)
{
	int	status;
	int	temp_status;
	int	j;

	disable_signals();
	if (i == pipe->pipes)
	{
		closing_pipes(pipe);
		j = 0;
		while (j < pipe->pipes)
		{
			waitpid(pipe->pids[j], &status, 0);
			if (status == 2 || status == 3)
				temp_status = status;
			if (status != 0 && status != 3 && temp_status != 2)
				temp_status = status;
			j++;
		}
		waitpid(pipe->pids[i], &status, 0);
		if (temp_status == 2)
			signal_handle_function(SIGINT);
		if (temp_status == 3)
			signal_handle_function(SIGQUIT);
		exit(WEXITSTATUS(status));
	}
}

void	pipex(t_command **cmds, char **envp, int pipes)
{
	t_pipe	pipe;
	int		i;
	pid_t	pid;

	init_pipe_strct(&pipe, pipes);
	set_pipes(&pipe);
	i = 0;
	while (i < pipes + 1)
	{
		pid = fork();
		if (pid == -1)
			exit(err_msg("FORK", 1));
		if (pid == 0)
			pipex_child(i, &pipe, cmds, envp);
		else
		{
			pipe.pids[i] = pid;
			pipex_parent(i, &pipe);
		}
		i++;
	}
}
