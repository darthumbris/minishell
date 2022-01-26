/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/26 10:48:16 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function parses the input
 * from the readline function.
 * it needs to handle double and single quotes
 * $ sign and also all the built-ins
 * like echo, cd, pwd etc.
 *	use dispached table to check all cases instead of if statement
 * echo with option -n
 */

void	cd_function(char **argv, char **env)
{
	return ;
}

void	pwd_function(char **argv, char **env)
{
	return ;
}

void	export_function(char **argv, char **env)
{
	return ;
}

void	unset_function(char **argv, char **env)
{
	return ;
}

void	env_function(char **argv, char **env)
{
	return ;
}

void	exit_function(char **argv, char **env)
{
	return ;
}

void	parse_input(char **argv, char **env)
{
	const t_functionPointer	function[] = {
	[CMD_CD] = &cd_function,
	[CMD_PWD] = &pwd_function,
	[CMD_EXPORT] = &export_function,
	[CMD_UNSET] = &unset_function,
	[CMD_ENV] = &env_function,
	[CMD_EXIT] = &exit_function,
		NULL
	};
	const char				*keys[] = {
	[CMD_CD] = "cd",
	[CMD_PWD] = "pwd",
	[CMD_EXPORT] = "export",
	[CMD_UNSET] = "unset",
	[CMD_ENV] = "env",
	[CMD_EXIT] = "exit",
		NULL
	};
	while (something < something)
	{

	}
}

int main(int argc, char **argv, char **envp)
{
	char	*input;

	parse_input(argv, envp);
	exit(0);
}
