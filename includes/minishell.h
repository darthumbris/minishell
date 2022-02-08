/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 14:11:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/08 14:15:14 by shoogenb      ########   odam.nl         */
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
# include "tokenizer.h"

typedef struct s_command
{
	char	**cmds;
	int		fd_in;
	int		fd_out;
	int		fd_error;
}				t_command;

void		free_cmd_args(char **cmd_args);
void		command_exec(char **paths, char **cmd_args, char **envp);
char		**get_cmd_arg(char *argv);
char		**get_path_str(char **envp);
char		**path_input(char *input);
char		*get_input(char *input);
void		execute_input(char *input, char **envp);
void		parse_input(t_command *cmd, char **envp);
int			minishell_thing(char *input, char **envp);
char		**envp_duplicate(char **envp);

char		*ft_getenv(char *str, char **envp);
void		signal_handle_function(int sig);

//---------Shell  Built-in-functions--------------
void		cd_function(t_command *cmd, char **envp);
void		pwd_function(t_command *cmd, char **envp);
void		export_function(t_command *cmd, char **envp);
void		unset_function(t_command *cmd, char **envp);
void		env_function(t_command *cmd, char **envp);
void		exit_function(t_command *cmd, char **envp);
void		echo_function(t_command *cmd, char **envp);

bool		is_valid_var_name(char *input);
void		identifier_msg(char *input, char *cmd, int fd);
void		export_simple(char *input, char **envp);

t_command	*new_command(char **cmds);
t_command	*create_cmd_lst(t_token *lst);
//char		*expand_env_variable(char *input, char **envp);
#endif