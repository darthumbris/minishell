/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 10:49:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/14 13:38:05 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *error_str, int return_val)
{
	perror(error_str);
	return (return_val);
}

/*
 * child process cmd2 reads from fd[0]
 * and writes to outfile fd created by the 
 * pipe function;
 * to this it needs to use dup2 to change
 * the stdin to end[0] and stdout to outfile fd
 */
void	child_process_cmd2(t_command *cmd2, char **envp, int fd[2])
{
	dup2(cmd2->fd_out, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	if (cmd2->fd_out != 1)
		close(cmd2->fd_out);
	parse_command(cmd2, envp);
}

/*
 * Child process cmd1 reads from the infile fd
 * and writes to fd[1] created by the 
 * pipe function;
 * to this it needs to use dup2 to change
 * the stdin to infile fd and stdout to fd[1]
 */
void	child_process_cmd1(t_command *cmd1, char **envp, int fd[2])
{
	dup2(cmd1->fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (cmd1->fd_in != 0)
		close(cmd1->fd_in);
	parse_command(cmd1, envp);
}

/*
 * This function will pipe the two commands
 * need to figure out how to properly do 
 * multiple pipes (redirection stuff is probably before this)
 */
int	pipex(t_command *cmd1, t_command *cmd2, char **envp)
{
	pid_t	child1_pid;
	pid_t	child2_pid;
	int		fd[2];
	int		status;

	pipe(fd);
	child1_pid = fork();
	if (child1_pid < 0)
		error_msg("FORK: ", 1);
	if (child1_pid == 0)
		child_process_cmd1(cmd1, envp, fd);
	child2_pid = fork();
	if (child2_pid < 0)
		error_msg("FORK: ", 1);
	if (child2_pid == 0)
		child_process_cmd2(cmd2, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(child1_pid, &status, 0);
	waitpid(child2_pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	new_pipex_multiple(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		// if (WIFEXITED(status) == 0 && status == 3)
		// 	signal_handle_function(SIGQUIT);
		// else if (WIFEXITED(status) == 0 && status == 2)
		// 	signal_handle_function(SIGINT);
	}
	else
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		parse_command(cmd, envp);
		waitpid(pid, &status, 0);
	}
	set_return_value(envp, WEXITSTATUS(status));
	return (status);
}
