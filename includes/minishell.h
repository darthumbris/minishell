/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 14:11:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/02 10:58:39 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <termios.h>
# include "command.h"

extern pid_t	g_pid;

//-----------Input get function------------
char		*get_input(char *input);
//----------Parsing functions-----------------
void		parse_command(t_command *cmd, char **envp, bool need_exit);
void		parse_input(char *input, char **envp);

//----------Execution functions-----------------
void		execute_input(t_command *cmd, char **envp);

#endif