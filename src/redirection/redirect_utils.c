/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 11:12:42 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/07 10:29:37 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

void	check_redir_out(t_token **lst, char **envp, t_command *cmd)
{
	if ((*lst) && (*lst)->token_name[0] == '>' && cmd->fd_out > 0)
	{
		cmd->fd_out = redirect_parse((*lst), envp, cmd->fd_out);
		(*lst) = (*lst)->next->next;
	}
	if ((*lst) && (*lst)->token_name[0] == '<' && cmd->fd_out > 0)
		check_redir_in(lst, envp, cmd);
	else if ((*lst) && (*lst)->token_name[0] == '>' && cmd->fd_out > 0)
		check_redir_out(lst, envp, cmd);
}

void	check_redir_in(t_token **lst, char **envp, t_command *cmd)
{
	if ((*lst) && (*lst)->token_name[0] == '<' && cmd->fd_in >= 0)
	{
		cmd->fd_in = redirect_parse((*lst), envp, cmd->fd_in);
		(*lst) = (*lst)->next->next;
	}
	if ((*lst) && (*lst)->token_name[0] == '>' && cmd->fd_in >= 0)
		check_redir_out(lst, envp, cmd);
	else if ((*lst) && (*lst)->token_name[0] == '<' && cmd->fd_in >= 0)
		check_redir_in(lst, envp, cmd);
}

void	close_fdio(int fd_in, int fd_out)
{
	if (fd_out > 2)
		close(fd_out);
	if (fd_in > 2)
		close(fd_in);
}
