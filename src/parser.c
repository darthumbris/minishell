/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/26 14:14:34 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_function(char *input)
{
	if (input && *input == ' ')
		printf("entered cd function correctly\n");
	printf("\n%d\n", ' ');
	return ;
}

void	pwd_function(char *input)
{
	if (input && *input == ' ')
		printf("entered pwd function\n");
	return ;
}

void	export_function(char *input)
{
	if (input && *input == ' ')
		printf("entered export function\n");
	return ;
}

void	unset_function(char *input)
{
	if (input && *input == ' ')
		printf("entered unset function\n");
	return ;
}

void	env_function(char *input)
{
	if (input && *input == ' ')
		printf("entered env function\n");
	return ;
}

void	exit_function(char *input)
{
	if (input && *input == ' ')
		printf("entered exit function\n");
	return ;
}

void	echo_function(char *input)
{
	if (input && *input == ' ')
		printf("entered echo function\n");
	return ;
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
	[CMD_CD] = &cd_function,
	[CMD_PWD] = &pwd_function,
	[CMD_EXPORT] = &export_function,
	[CMD_UNSET] = &unset_function,
	[CMD_ENV] = &env_function,
	[CMD_EXIT] = &exit_function,
	[CMD_ECHO] = &echo_function,
		NULL
	};
	const char				*keys[] = {
	[CMD_CD] = "cd",
	[CMD_PWD] = "pwd",
	[CMD_EXPORT] = "export",
	[CMD_UNSET] = "unset",
	[CMD_ENV] = "env",
	[CMD_EXIT] = "exit",
	[CMD_ECHO] = "echo",
		NULL
	};
	int						i;

	i = 0;
	while (*input && *input == ' ')
		input++;
	while (keys[i])
	{
		if (ft_strncmp(input, keys[i], ft_strlen(keys[i])) == 0)
			return (function[i](input + ft_strlen(keys[i])));
		i++;
	}
	minishell_thing(input, envp);
}
