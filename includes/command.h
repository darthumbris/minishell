/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 10:25:17 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/03 12:32:03 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "tokenizer.h"

typedef struct s_command
{
	char	**cmds;
	int		fd_in;
	int		fd_out;
	int		fd_error;
	char	**delimiter;
	int		heredocs;
}				t_command;

//------------command struct functions----------
t_command	*new_command(char **cmds);
t_command	**get_commands(t_token *lst, int cmd_cnt, char **envp);

//----------Freeing functions-----------------
void		free_cmd_lst(t_command ***cmds);
void		free_cmds(t_command *cmd);
void		free_cmd_args(char **cmd_args);

#endif