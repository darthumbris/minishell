/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 10:49:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/02 12:09:16 by shoogenb      ########   odam.nl         */
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
void	child_process_cmd2(int outfile_fd, char **argv, char **envp, int fd[2])
{
	char	**paths;
	char	**cmd_args;

	paths = get_path_str(envp);
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(outfile_fd);
	cmd_args = get_cmd_arg(argv[3]);
	command_exec(paths, cmd_args, envp);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_cmd_args(cmd_args);
	exit(127);
}

/*
 * Child process cmd1 reads from the infile fd
 * and writes to fd[1] created by the 
 * pipe function;
 * to this it needs to use dup2 to change
 * the stdin to infile fd and stdout to fd[1]
 */
void	child_process_cmd1(int infile_fd, char **argv, char **envp, int fd[2])
{
	char	**paths;
	char	**cmd_args;

	paths = get_path_str(envp);
	dup2(infile_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(infile_fd);
	cmd_args = get_cmd_arg(argv[2]);
	command_exec(paths, cmd_args, envp);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_cmd_args(cmd_args);
	exit(127);
}

/*
 * This function will pipe the two commands
 * need to figure out how to properly do 
 * multiple pipes (redirection stuff is probably before this)
 */
int	pipex(t_command cmd1, t_command cmd2, char **envp)
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
		child_process_cmd1(cmd1.fd_in, cmd1.cmds, envp, fd);
	child2_pid = fork();
	if (child2_pid < 0)
		error_msg("FORK: ", 1);
	if (child2_pid == 0)
		child_process_cmd2(cmd2.fd_out, cmd2.cmds, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(child1_pid, &status, 0);
	waitpid(child2_pid, &status, 0);
	return (WEXITSTATUS(status));
}
