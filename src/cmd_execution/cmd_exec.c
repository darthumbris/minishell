/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 13:41:02 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/03 17:08:05 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"
#include "dirent.h"

/*
 * This function will give the absolute path back
 * needed to execute things. (might not be needed)
 * can be replaced with getenv("PATH=", envp)!!!
 */
static char	**path_input(char *input)
{
	char	**paths;

	paths = ft_calloc(2, sizeof(char *));
	if (!paths)
		return (NULL);
	paths[0] = ft_substr(input, 0, ft_strrchr(input, '/') - input);
	return (paths);
}

/*
 * This function will get all the paths
 * located in the envp variable
 */
static char	**get_path_str(char **envp)
{
	if (envp)
	{
		if (ft_getenv("PATH", envp))
			return (ft_split(ft_getenv("PATH", envp), ':'));
	}
	return (NULL);
}

/*
 * The Access check is there to check if the command is actually
 * an executable file.
 * It will loop through all the paths in the envp to look
 * for the command to execute.
 */
static void	command_exec(char **paths, char **cmd_args, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*cmd_slash;

	i = 0;
	if (cmd_args)
		cmd_slash = ft_strjoin("/", cmd_args[0]);
	else
		cmd_slash = ft_strdup("");
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd_slash);
		if (!access(cmd_path, 0))
			execve(cmd_path, cmd_args, envp);
		free(cmd_path);
		i++;
	}
	free(cmd_slash);
}

static void	execute_error(char *input, int fd_error, char **paths)
{
	ft_putstr_fd("minishell: ", fd_error);
	ft_putstr_fd(input, fd_error);
	free(input);
	if (paths && opendir(paths[0]) && input[0] != '/')
	{
		free_cmd_args(paths);
		ft_putendl_fd(": command not found", fd_error);
		exit(127);
	}
	else if (paths && opendir(paths[0]))
	{
		free_cmd_args(paths);
		ft_putendl_fd(": No such file or directory", fd_error);
		exit(127);
	}
	else
		ft_putendl_fd(": Not a directory", fd_error);
	exit(126);
}

/*
 * 
 */
void	execute_input(t_command *cmd, char **envp)
{
	char	**paths;
	char	*input;

	input = ft_strdup(cmd->cmds[0]);
	if (input && *input == '/')
	{
		paths = path_input(input);
		free(cmd->cmds[0]);
		cmd->cmds[0] = ft_substr(input, ft_strlen(paths[0]), ft_strlen(input));
	}
	else if (input && *input == '.' && input[1] == '/')
		paths = path_input(input);
	else
		paths = get_path_str(envp);
	if (paths)
		command_exec(paths, cmd->cmds, envp);
	execute_error(input, cmd->fd_error, paths);
}
