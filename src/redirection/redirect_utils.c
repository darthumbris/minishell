/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 11:12:42 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/01 13:57:17 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_and_close(int *fd, int std)
{
	if (*fd != std)
	{
		dup2(*fd, std);
		close(*fd);
		*fd = std;
	}
}

void	dup_and_close_redirect(int *fd, int std, t_token **lst, char **envp)
{
	fprintf(stderr, "hey\n");
	dup_and_close(fd, std);
	*fd = redirect_parse((*lst), envp);
}

void	check_redir_out(t_token **lst, char **envp, t_command *cmd)
{
	if ((*lst) && (*lst)->token_name[0] == '>')
	{
		dup_and_close(&(cmd->fd_out), STDOUT_FILENO);
		cmd->fd_out = redirect_parse((*lst), envp);
		(*lst) = (*lst)->next->next;
	}
	if ((*lst) && (*lst)->token_name[0] == '<')
		check_redir_in(lst, envp, cmd);
	else if ((*lst) && (*lst)->token_name[0] == '>')
		check_redir_out(lst, envp, cmd);
}

void	check_redir_in(t_token **lst, char **envp, t_command *cmd)
{
	if ((*lst) && (*lst)->token_name[0] == '<')
	{
		dup_and_close(&(cmd->fd_in), STDIN_FILENO);
		cmd->fd_in = redirect_parse((*lst), envp);
		(*lst) = (*lst)->next->next;
	}
	if ((*lst) && (*lst)->token_name[0] == '>')
		check_redir_out(lst, envp, cmd);
	else if ((*lst) && (*lst)->token_name[0] == '<')
		check_redir_in(lst, envp, cmd);
}
