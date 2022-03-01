/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/28 16:23:06 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dispatch.h"
#include "tokenizer.h"

/*
 * This function parses the command.
 * It will check if the command it gets is 
 * one of the built-in functions otherwise
 * it will send it to the execute input function.
 */
void	parse_command(t_command *cmd, char **envp)
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
	{"echo", &echo_function}, {0, NULL}
	};

	i = 0;
	while (function[i].comand != 0)
	{
		len = ft_strlen(function[i].comand);
		if (ft_strncmp(cmd->cmds[0], function[i].comand, len) == 0 && \
			(cmd->cmds[0][len] == '\0' || cmd->cmds[0][len] == ' '))
		{
			function[i].t_function_pointer(cmd, envp);
			exit(ft_atoi(envp[0]));
		}
		i++;
	}
	execute_input(cmd, envp);
}
