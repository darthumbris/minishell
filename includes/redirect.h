/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 10:33:35 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/02 10:34:30 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "tokenizer.h"
# include "command.h"

//------------redirection functions--------------
void		dup_and_close_redirect(int *fd, int std, \
							t_token **lst, char **envp);
void		check_redir_in(t_token **lst, char **envp, t_command *cmd);
void		check_redir_out(t_token **lst, char **envp, t_command *cmd);
void		redirect(t_command *cmd, int pid);
int			redirect_parse(t_token *lst, char **envp);

#endif