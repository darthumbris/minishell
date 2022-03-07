/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 10:33:35 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/07 10:27:50 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "tokenizer.h"
# include "command.h"

//------------redirection functions--------------
void		check_redir_in(t_token **lst, char **envp, t_command *cmd);
void		check_redir_out(t_token **lst, char **envp, t_command *cmd);
void		redirect(t_command *cmd, int pid);
int			redirect_parse(t_token *lst, char **envp, int fd);
void		close_fdio(int fd_in, int fd_out);
#endif