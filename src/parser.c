/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/27 13:44:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dispatch.h"

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
	[CMD_ENV] = "env", [CMD_EXIT] = "exit", [CMD_ECHO] = "echo", NULL
	};
	int						i;
	int						len;

	i = 0;
	input = ft_whitespaces(input);
	while (keys[i])
	{
		len = ft_strlen(keys[i]);
		if (ft_strncmp(input, keys[i], len) == 0 && \
			(input[len] == '\0' || input[len] == ' '))
			return (function[i](input + len, envp));
		i++;
	}
	minishell_thing(input, envp);
}
