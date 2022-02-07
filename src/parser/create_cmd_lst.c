/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd_lst.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 14:28:29 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/07 16:22:27 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function will check
 * how big the cmd args are
 * for the cmd struct.
 */
int	count_cmd_args(t_token *lst)
{
	t_token	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		if (tmp->token_name[0] != 'W')
			break ;
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	free_cmds(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmds[i])
	{
		free(cmd->cmds[i]);
		i++;
	}
	free(cmd->cmds);
	free(cmd);
}

/*
 * This function will create a command struct
 * using the token list. Basically
 * a word token will be converted to a command
 * if there are multiple word tokens
 * after each other they will be converted
 * to a cmd_arg array
 * where cmd_arg[0] is the command
 * and all the others in the array
 * are the arguments or options.
 */
void	create_cmd_lst(t_token *lst, char **envp)
{
	t_token		*tmp;
	t_command	*cmd;
	char		**cmds;
	int			len;
	int			i;

	tmp = lst;
	while (tmp)
	{
		if (tmp->token_name[0] == 'W')
		{
			len = count_cmd_args(tmp);
			cmds = ft_calloc(len + 1, sizeof(char *));
			i = 0;
			while (i < len)
			{
				cmds[i++] = ft_strdup(tmp->token_value);
				tmp = tmp->next;
			}
			if (tmp)
				printf("now at command: %s\n", tmp->token_value);
			cmd = new_command(cmds);
			parse_input(cmd, envp);
			free_cmds(cmd);
		}
		else
			tmp = tmp->next;
	}
}
