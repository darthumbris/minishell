/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_function.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 12:25:01 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/04 10:55:08 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	export_simple(char *input, char **envp)
{
	t_command	*temp;
	char		**cmds;

	cmds = ft_calloc(3, sizeof(char *));
	if (cmds)
		cmds[1] = input;
	temp = new_command(cmds);
	export_function(temp, envp);
	free_cmd_args(cmds);
	free(temp);
}

/*
 * This function will check if the variable
 * name is a valid. A variable name
 * can't begin with a digit.
 * and can only contain A-Z a-z 0-9 and _
 */
bool	is_valid_var_name(char *input)
{
	int	i;

	if (input)
	{
		if (!ft_isdigit(input[0]))
		{
			i = 0;
			while (input[i])
			{
				if (!ft_isalnum(input[i]) && input[i] != '_')
					break ;
				i++;
			}
			if (i && (input[i] == '=' || input[i] == '\0'))
				return (true);
		}
	}
	return (false);
}

/*
 * This function will set the variable
 * and its value into the envp list.
 */
static	void	set_env(char **envp, char *input)
{
	char	*export_var;
	int		i;

	export_var = ft_substr(input, 0, ft_strchr(input, '=') - input);
	i = 2;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], export_var, ft_strlen(export_var)) == 0)
		{
			free(envp[i]);
			envp[i] = NULL;
			break ;
		}
		i++;
	}
	i = 2;
	while (envp[i])
		i++;
	envp[i] = ft_strdup(input);
	free(export_var);
}

static void	print_export(char **envp)
{
	int	i;

	i = 2;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

/*
 * This function handles the export function
 * export can handle stuff like: export test=water like=bake
 * and will do both arguments.
 * need to check if there are no arguments given.
 * variable cant start with digit
 * and can only contain A-Z a-z 0-9 or _
 * can only export something when it is given a value
 * i.e. export a=b  will work
 * export a won't work
 * export a= will also work
 */
void	export_function(t_command *cmd, char **envp)
{
	int		i;
	int		error;

	error = 0;
	if (cmd && cmd->cmds)
	{
		i = 1;
		while (cmd->cmds[i])
		{
			if (!is_valid_var_name(cmd->cmds[i]))
			{
				identifier_msg(cmd->cmds[i], cmd->cmds[0], cmd->fd_out);
				error = 1;
			}
			else
				set_env(envp, cmd->cmds[i]);
			i++;
		}
		if (i == 1)
			print_export(envp);
	}
	set_return_value(envp, error);
}
