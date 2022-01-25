/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 13:41:02 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/25 13:41:02 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_str(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 5))
			return (ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i])), ':'));
		i++;
	}
	return (NULL);
}

char	**get_cmd_arg(char *argv)
{
	char	**cmd_args;

	cmd_args = ft_split(argv, ' ');
	return (cmd_args);
}

/*
 * The Access check is there to check if the command is actually
 * an executable file.
 * It will loop through all the paths in the envp to look
 * for the command to execute.
 */
void	command_exec(char **paths, char **cmd_args, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*cmd_slash;

	i = 0;
	cmd_slash = ft_strjoin("/", cmd_args[0]);
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

void	free_cmd_args(char **cmd_args)
{
	int	i;

	i = 0;
	if (cmd_args)
	{
		while (cmd_args[i])
		{
			free(cmd_args[i]);
			i++;
		}
		free(cmd_args);
	}
}
