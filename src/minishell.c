/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/25 14:32:07 by shoogenb      ########   odam.nl         */
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
 * For now the check input will handle the case with absolute path
 * and using envp. Wont work yet with relative path.
 * The get_cmd_args that it uses also doesn't yet handle quotes
 * and other difficult stuff.
 * things like echo $? or echo $USER and other commands.
 * will also give wrong error when doing absolute path stuff
 * for example /bin/wc will give command not found
 * instead of no such file or directory.
 */
void	check_input(char *input, char **envp)
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

/*
 * This function will create the child process to handle the simple 
 * commands. Won't work yet with pipe.
 * Also the return value required for the echo $? needs to be done
 */
int	minishell_thing(char *input, char **envp)
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
		check_input(input, envp);
	waitpid(child_pid, &status, 0);
	return (WEXITSTATUS(status));
}

/*
 * This function handles the ctrl-c for now
 * it will make a new line and clear the input.
 */
void	signal_handle_function(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		printf("ctrl-c \n");
	}
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

int	main(int argc, char **argv, char **envp)
{
	static char	*input;

	input = NULL;
	if (argc != 1 || !argv || !envp)
		return (1);
	signal(SIGINT, signal_handle_function);
	while (1)
	{
		input = get_input(input);
		if (input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (input && *input)
			minishell_thing(input, envp);
	}
	return (0);
}
