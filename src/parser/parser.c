/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 10:53:59 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dispatch.h"
#include "tokenizer.h"

int	count_pipes(t_token *lst, char **envp)
{
	t_token		*tmp;
	int			pipe_cnt;

	tmp = lst;
	pipe_cnt = 0;
	while (tmp && envp)
	{
		if (tmp->token_name[0] == '|')
			pipe_cnt++;
		if (tmp)
			tmp = tmp->next;
	}
	return (pipe_cnt);
}

void	dup_and_close(int *fd, int std)
{
	if (*fd != std)
	{
		dup2(*fd, std);
		close(*fd);
		*fd = std;
	}
}

void	check_redir_out(t_token **lst, char **envp, t_command *cmd)
{
	if ((*lst) && (*lst)->token_name[0] == '>')
	{
		dup_and_close(&(cmd->fd_out), STDOUT_FILENO);
		cmd->fd_out = redirect_parse((*lst), envp);
		(*lst) = (*lst)->next->next;
	}
	if ((*lst) && ((*lst)->token_name[0] == '<' || \
		(*lst)->token_name[0] == 'h'))
		check_redir_in(lst, envp, cmd);
	else if ((*lst) && (*lst)->token_name[0] == '>')
		check_redir_out(lst, envp, cmd);
}

void	check_redir_in(t_token **lst, char **envp, t_command *cmd)
{
	if ((*lst) && ((*lst)->token_name[0] == '<' || \
		(*lst)->token_name[0] == 'h'))
	{
		dup_and_close(&(cmd->fd_in), STDIN_FILENO);
		cmd->fd_in = redirect_parse((*lst), envp);
		(*lst) = (*lst)->next->next;
	}
	if ((*lst) && (*lst)->token_name[0] == '>')
		check_redir_out(lst, envp, cmd);
	else if ((*lst) && ((*lst)->token_name[0] == '<' || \
		(*lst)->token_name[0] == 'h'))
		check_redir_in(lst, envp, cmd);
}

/*
 * This function parses the command.
 * It will check if the command it gets is 
 * one of the built-in functions otherwise
 * it will send it to the execute input function.
 */
void	parse_command(t_command *cmd, char **envp)
{
	int						i;
	int						len;
	const t_cmd				function[] = {
	{"cd", &cd_function},
	{"pwd", &pwd_function},
	{"export", &export_function},
	{"unset", &unset_function},
	{"env", &env_function},
	{"exit", &exit_function},
	{"echo", &echo_function}, {0, NULL}
	};

	i = 0;
	while (function[i].comand != 0)
	{
		len = ft_strlen(function[i].comand);
		if (ft_strncmp(cmd->cmds[0], function[i].comand, len) == 0 && \
			(cmd->cmds[0][len] == '\0' || cmd->cmds[0][len] == ' '))
		{
			function[i].t_function_pointer(cmd, envp);
			exit(ft_atoi(envp[0]));
		}
		i++;
	}
	execute_input(cmd, envp);
}
