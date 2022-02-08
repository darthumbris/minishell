/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 15:41:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/08 15:42:22 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function will create the child process to handle the simple 
 * commands. Won't work yet with pipe.
 * Also the return value required for the echo $? needs to be done
 * THIS FUNCTION IS TEMPORARY UNTIL PIPE ETC IS WORKING!!!!.
 * or need to change it in case there is only one command (no pipes)
 */
int	single_command(t_command *cmd, char **envp)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("FORK: ");
		return (1);
	}
	if (child_pid == 0)
		execute_input(cmd, envp);
	waitpid(child_pid, &status, 0);
	return (WEXITSTATUS(status));
}

/*
 * For now the check input will handle the case with absolute path
 * and using envp. Wont work yet with relative path.
 * The get_cmd_args that it uses also doesn't yet handle quotes
 * and other difficult stuff.
 * things like echo $? or echo $USER and other commands.
 * will also give wrong error when doing absolute path stuff
 * for example /bin/wc will give command not found
 * instead of no such file or directory.
 */
void	execute_input(t_command *cmd, char **envp)
{
	char	**paths;
	char	*input;

	input = cmd->cmds[0];
	if (input && (*input == '/' || (*input == '.' && input[1] == '/')))
		paths = path_input(input);
	else
		paths = get_path_str(envp);
	command_exec(paths, cmd->cmds, envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmds[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}
