/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 14:38:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/25 14:43:50 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function will give the absolute path back
 * needed to execute things.
 */
char	**path_input(char *input)
{
	char	**paths;

	paths = ft_calloc(2, sizeof(char *));
	if (!paths)
		return (NULL);
	paths[0] = ft_substr(input, 0, ft_strchr(input + 1, '/') - input);
	return (paths);
}

/*
 * This functions uses readline to get input
 * in the shell and will add it to the history
 * when needed (so no empty stuff).
 * It will also close when EOF (ctrl-D)
 * this might need some work for some cases.
 */
char	*get_input(char *input)
{
	if (input)
	{
		free(input);
		input = NULL;
	}
	input = readline("minishell> ");
	if (input && *input)
	{
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			free(input);
			printf("exit\n");
			exit(0);
		}
		add_history(input);
	}
	return (input);
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
void	execute_input(char *input, char **envp)
{
	char	**paths;
	char	**cmd_args;

	if (input && *input == '/')
	{
		paths = path_input(input);
		cmd_args = get_cmd_arg(input + (ft_strchr(input + 1, '/') - input + 1));
	}
	else
	{
		paths = get_path_str(envp);
		cmd_args = get_cmd_arg(input);
	}
	command_exec(paths, cmd_args, envp);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_cmd_args(cmd_args);
	exit(127);
}
