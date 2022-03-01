/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 14:11:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/01 11:58:33 by shoogenb      ########   odam.nl         */
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

pid_t	g_pid;

typedef struct s_command
{
	char	**cmds;
	int		fd_in;
	int		fd_out;
	int		fd_error;
	char	**delimiter;
	int		heredocs;
}				t_command;

void		free_cmd_args(char **cmd_args);
char		**path_input(char *input);
char		*get_input(char *input);
void		execute_input(t_command *cmd, char **envp);
void		parse_command(t_command *cmd, char **envp);
char		**envp_duplicate(char **envp);
void		set_return_value(char **envp, int nbr);

char		*ft_getenv(char *str, char **envp);

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
void		free_cmds(t_command *cmd);
bool		is_valid_exit(t_command *cmd);
void		dup_and_close(int *fd, int std);
void		check_redir_in(t_token **lst, char **envp, t_command *cmd);
void		check_redir_out(t_token **lst, char **envp, t_command *cmd);
t_command	**get_commands(t_token *lst, int cmd_cnt, char **envp);
void		pipex(t_command **cmds, char **envp, int pipes);
void		redirect(t_command *cmd, int pid);
void		free_cmd_lst(t_command **cmds);
void		parse_input(char *input, char **envp);

void		set_signals(void);
void		disable_signals(void);
void		signal_handle_function(int sig);
char		**get_delimiter(t_token *lst);
bool		check_heredoc(t_token **lst, t_command *cmd);
void		heredoc_with_command(t_command *cmd, char **envp);
void		signal_heredoc(int sig);
void		free_delimiter(char **delimiter);
#endif