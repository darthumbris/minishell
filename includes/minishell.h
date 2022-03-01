/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 14:11:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/01 15:49:40 by shoogenb      ########   odam.nl         */
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
# include <termios.h>

extern pid_t	g_pid;

typedef struct s_command
{
	char	**cmds;
	int		fd_in;
	int		fd_out;
	int		fd_error;
	char	**delimiter;
	int		heredocs;
}				t_command;

//-----------Input get function------------
char		*get_input(char *input);
//----------Parsing functions-----------------
void		parse_command(t_command *cmd, char **envp);
void		parse_input(char *input, char **envp);
//---------Shell  Built-in-functions--------------
void		cd_function(t_command *cmd, char **envp);
void		pwd_function(t_command *cmd, char **envp);
void		export_function(t_command *cmd, char **envp);
void		unset_function(t_command *cmd, char **envp);
void		env_function(t_command *cmd, char **envp);
void		exit_function(t_command *cmd, char **envp);
void		echo_function(t_command *cmd, char **envp);
//---------Shell  Built-in-functions Utils--------------
bool		is_valid_var_name(char *input);
void		identifier_msg(char *input, char *cmd, int fd);
bool		is_valid_exit(t_command *cmd);
//----------envp functions------------------------
void		export_simple(char *input, char **envp);
void		change_shl_lvl(char **envp, int change);
char		**envp_duplicate(char **envp);
void		set_return_value(char **envp, int nbr);
char		*ft_getenv(char *str, char **envp);
//------------command struct functions----------
t_command	*new_command(char **cmds);
t_command	**get_commands(t_token *lst, int cmd_cnt, char **envp);
//----------Execution functions-----------------
void		pipex(t_command **cmds, char **envp, int pipes);
void		execute_input(t_command *cmd, char **envp);
//------------redirection functions--------------
void		dup_and_close_redirect(int *fd, int std, \
							t_token **lst, char **envp);
void		check_redir_in(t_token **lst, char **envp, t_command *cmd);
void		check_redir_out(t_token **lst, char **envp, t_command *cmd);
void		redirect(t_command *cmd, int pid);
int			redirect_parse(t_token *lst, char **envp);
//----------Freeing functions-----------------
void		free_cmd_lst(t_command **cmds);
void		free_cmds(t_command *cmd);
void		free_cmd_args(char **cmd_args);
//------------Signal Functions---------------
void		set_signals(void);
void		disable_signals(void);
void		signal_handle_function(int sig);
void		signal_heredoc(int sig);
//-----------Heredoc Functions----------------------
char		**get_delimiter(t_token *lst);
bool		check_heredoc(t_token **lst, t_command *cmd);
void		heredoc_with_command(t_command *cmd, char **envp);
void		free_delimiter(char **delimiter);
char		*expand_input(char *line, char **envp);
int			heredoc_function(t_token *lst, char **envp);
#endif