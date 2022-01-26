/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 14:11:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/26 14:03:51 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "libft.h"
# include <signal.h>

enum e_builtins
{
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_ECHO
};
typedef void(*t_functionPointer)(char *input);

void	free_cmd_args(char **cmd_args);
void	command_exec(char **paths, char **cmd_args, char **envp);
char	**get_cmd_arg(char *argv);
char	**get_path_str(char **envp);
char	**path_input(char *input);
char	*get_input(char *input);
void	execute_input(char *input, char **envp);
void	parse_input(char *input, char **envp);
int		minishell_thing(char *input, char **envp);
#endif