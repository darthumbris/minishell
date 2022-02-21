/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_exit_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 11:13:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/21 13:31:23 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

/*
 * This function checks the token list
 * for the exit command. And there should only be one exit command.
 * otherwise in bash it won't actually exit.
 * i.e. : exit | exit won't exit bash.
 */
t_command	*get_exit_cmd(t_token *lst)
{
	t_token		*tmp;
	t_command	*last_cmd;
	int			cmd_count;

	tmp = lst;
	last_cmd = new_command(NULL);
	cmd_count = 0;
	while (tmp)
	{
		if (tmp->token_name[0] == 'W')
		{
			cmd_count++;
			if (last_cmd->cmds)
				free_cmd_args(last_cmd->cmds);
			last_cmd = create_cmd_lst(&tmp, last_cmd, NULL);
		}
		if (tmp)
			tmp = tmp->next;
	}
	if (last_cmd->cmds && cmd_count == 1 && \
		ft_strcmp(last_cmd->cmds[0], "exit") == 0)
		return (last_cmd);
	free(last_cmd);
	return (NULL);
}
