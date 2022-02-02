/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 14:11:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/02 13:08:04 by shoogenb      ########   odam.nl         */
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
# include <dirent.h>

void		free_cmd_args(char **cmd_args);
void		command_exec(char **paths, char **cmd_args, char **envp);
char		**get_cmd_arg(char *argv);
char		**get_path_str(char **envp);
char		**path_input(char *input);
char		*get_input(char *input);
void		execute_input(char *input, char **envp);
void		parse_input(char *input, char **envp);
int			minishell_thing(char *input, char **envp);
char		**envp_duplicate(char **envp);

char		*ft_getenv(char *str, char **envp);
void		change_pwd_in_envp(char **envp);
void		signal_handle_function(int sig);
void		change_shl_lvl(char **envp, int change);
t_command	*new_command(char **cmds);

//---------Shell  Built-in-functions--------------
void		cd_function(char *input, char **envp);
void		pwd_function(char *input, char **envp);
void		export_function(char *input, char **envp);
void		unset_function(char *input, char **envp);
void		env_function(char *input, char **envp);
void		exit_function(char *input, char **envp);
void		echo_function(char *input, char **envp);

//maybe the arguments should be a linked lists?
typedef struct s_command
{
	char	**cmds;
	int		fd_in;
	int		fd_out;
	int		fd_error;
}				t_command;
#endif