/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd_lst.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 14:28:29 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/14 12:22:37 by shoogenb      ########   odam.nl         */
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
		//printf("freeing cmds[%d]\n", i);
		free(cmd->cmds[i]);
		i++;
	}
	//printf("freeing cmds\n");
	free(cmd->cmds);
	//printf("freeing cmd\n");
	free(cmd);
	cmd = NULL;
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
t_command	*create_cmd_lst(t_token **lst, t_command *cmd)
{
	char		**cmds;
	int			len;
	int			i;

	if ((*lst)->token_name[0] == 'W')
	{
		len = count_cmd_args((*lst));
		cmds = ft_calloc(len + 1, sizeof(char *));
		i = 0;
		while (i < len)
		{
			cmds[i++] = ft_strdup((*lst)->token_value);
			(*lst) = (*lst)->next;
		}
		cmd->cmds = cmds;
		return (cmd);
	}
	return (NULL);
}
