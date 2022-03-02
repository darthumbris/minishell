/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 10:29:07 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/02 10:32:24 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "tokenizer.h"
# include "command.h"

//-----------Heredoc Functions----------------------
char		**get_delimiter(t_token *lst);
bool		check_heredoc(t_token **lst, t_command *cmd);
void		heredoc_with_command(t_command *cmd, char **envp);
void		free_delimiter(char **delimiter);
char		*expand_input(char *line, char **envp);
int			heredoc_function(t_token *lst, char **envp);

#endif