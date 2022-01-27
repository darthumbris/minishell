/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/26 20:27:32 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dispatch.h"

/*
 * The cd function will check the input 
 * and then try to change the directory with
 * chdir.
 */
void	cd_function(char *input)
{
	input = ft_whitespaces(input);
	if (!*input)
	{
		if (chdir(getenv("HOME")) == -1)
			perror("testing");
	}
	else
	{
		if (chdir(input) == -1)
			perror("");
	}
}

void	pwd_function(char *input)
{
	char	*pwd_str;

	if (input && !ft_isalpha(*input) && !ft_isdigit(*input))
	{
		pwd_str = getcwd(NULL, -1);
		printf("%s.................\n", pwd_str);
		free(pwd_str);
	}
}

void	export_function(char *input)
{
	if (input && *input == ' ')
		printf("entered export function\n");
}

void	unset_function(char *input)
{
	if (input && *input == ' ')
		printf("entered unset function\n");
}

void	env_function(char *input)
{
	if (input && *input == ' ')
		printf("entered env function\n");
	printf("entered env function\n");
}

void	exit_function(char *input)
{
	if (input && !ft_isalpha(*input) && !ft_isdigit(*input))
	{
		//printf("entered exit function\n");
		//free(input);
		printf("exit\n");
		system("leaks minishell");
		exit(0);
	}
	else
	{
		ft_putstr_fd("exit", 2);
		ft_putstr_fd(input, 2);
		ft_putendl_fd(": command not found", 2);
	}
}

void	echo_function(char *input)
{
	if (input && *input == ' ')
		printf("entered echo function\n");
}

/*
 * This function parses the input
 * from the readline function.
 * it needs to handle double and single quotes
 * $ sign and also all the built-ins
 * like echo, cd, pwd etc.
 * need to also take into account whitespace
 * before the command (i.e.:       pwd should still execute)
 * need to also check that it won't work with : cdb or something
 */
void	parse_input(char *input, char **envp)
{
	const t_functionPointer	function[] = {
	[CMD_CD] = &cd_function, [CMD_PWD] = &pwd_function,
	[CMD_EXPORT] = &export_function, [CMD_UNSET] = &unset_function,
	[CMD_ENV] = &env_function, [CMD_EXIT] = &exit_function,
	[CMD_ECHO] = &echo_function, NULL
	};
	const char				*keys[] = {
	[CMD_CD] = "cd", [CMD_PWD] = "pwd",
	[CMD_EXPORT] = "export", [CMD_UNSET] = "unset",
	[CMD_ENV] = "env", [CMD_EXIT] = "exit",
	[CMD_ECHO] = "echo", NULL
	};
	int						i;

	i = 0;
	input = ft_whitespaces(input);
	while (keys[i])
	{
		if (ft_strncmp(input, keys[i], ft_strlen(keys[i])) == 0)
			return (function[i](input + ft_strlen(keys[i])));
		i++;
	}
	minishell_thing(input, envp);
}
