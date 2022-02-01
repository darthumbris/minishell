/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/01 12:15:32 by shoogenb      ########   odam.nl         */
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
	int						i;
	int						len;
	const t_cmd				function[] = {
	{"cd", &cd_function},
	{"pwd", &pwd_function},
	{"export", &export_function},
	{"unset", &unset_function},
	{"env", &env_function},
	{"exit", &exit_function},
	{"echo", &echo_function},
	{0, NULL}
	};

	i = 0;
	input = ft_whitespaces(input);
	while (function[i].comand != 0)
	{
		len = ft_strlen(function[i].comand);
		if (ft_strncmp(input, function[i].comand, len) == 0 && \
			(input[len] == '\0' || input[len] == ' '))
			return (function[i].t_function_pointer(input + len, envp));
		i++;
	}
	minishell_thing(input, envp);
}
