/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 14:11:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/21 15:53:33 by shoogenb      ########   odam.nl         */
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
	int		ret;
}				t_command;

void		free_cmd_args(char **cmd_args);
void		command_exec(char **paths, char **cmd_args, char **envp);
char		**get_cmd_arg(char *argv);
char		**get_path_str(char **envp);
char		**path_input(char *input);
char		*get_input(char *input);
void		execute_input(t_command *cmd, char **envp);
void		parse_command(t_command *cmd, char **envp);
//int			single_command(t_command *cmd, char **envp);
char		**envp_duplicate(char **envp);
void		set_return_value(char **envp, int nbr);
void		set_pid(char **envp, pid_t	pid);

char		*ft_getenv(char *str, char **envp);
void		signal_handle_function(int sig);
void		signal_handle_child(int sig);

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
void		change_shl_lvl(char **envp, int change);
int			heredoc_function(t_token *lst, char **envp);
int			redirect_parse(t_token *lst, char **envp);

t_command	*new_command(char **cmds);
t_command	*create_cmd_lst(t_token **lst, t_command *cmd, char **envp);
void		free_cmds(t_command *cmd);
//char		*expand_env_variable(char *input, char **envp);
int			pipex(t_command *cmd1, t_command *cmd2, char **envp);
int			new_pipex_multiple(t_command *cmd, char **envp);
void		parse_token_lst(t_token *lst, char **envp);
bool		is_command_valid(t_command *cmd, char **envp, int i, char *input);
void		err_cmd_not_found(char *cmd);
t_command	*get_exit_cmd(t_token *lst);
bool		is_valid_exit(t_command *cmd);
void		check_valid_commands(t_token *lst, char **envp);
bool		is_first_command_empty_cat(t_token *lst);
int			count_cmd_args(t_command *cmd);
t_command	*get_next_command(t_token **lst, char **envp);
int			count_pipes(t_token *lst, char **envp);
void		parse_token_lst_with_pipe(t_token *lst, char **envp);
void		dup_and_close(int *fd, int std);
void		check_redir_in(t_token **lst, char **envp, t_command *cmd);
void		check_redir_out(t_token **lst, char **envp, t_command *cmd);
t_command	**get_commands(t_token *lst, t_command *cmd, int cmd_cnt, char **envp);
#endif