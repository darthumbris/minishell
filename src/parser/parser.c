/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/14 13:42:56 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dispatch.h"
#include "tokenizer.h"

static int	parse_redirection(t_token *lst, char **envp, t_command *cmd)
{
	t_token		*tmp;
	int			pipe_cnt;

	tmp = lst;
	pipe_cnt = 0;
	while (tmp)
	{
		if (tmp->token_name[0] == '<')
			cmd->fd_in = redirect_parse(tmp, envp);
		else if (tmp->token_name[0] == '>')
			cmd->fd_out = redirect_parse(tmp, envp);
		else if (tmp->token_name[0] == '|')
			pipe_cnt++;
		tmp = tmp->next;
	}
	return (pipe_cnt);
}

static void	parse_command_lst(t_token *tmp, char **envp, \
	t_command *cmd, int pipe_cnt)
{
	int	temp_status;
	int	status;

	status = 0;
	while (tmp)
	{
		if (tmp->token_name[0] == 'W')
		{
			if (cmd->cmds)
				free_cmd_args(cmd->cmds);
			cmd = create_cmd_lst(&tmp, cmd);
		}
		if (pipe_cnt && cmd && cmd->cmds)
		{
			temp_status = new_pipex_multiple(cmd, envp);
			if (temp_status == 2 || temp_status == 3)
				status = temp_status;
			pipe_cnt--;
		}
		else if (cmd && cmd->cmds)
		{
			if (WIFEXITED(status) == 0 && status == 3)
				signal_handle_function(SIGQUIT);
			else if (WIFEXITED(status) == 0 && status == 2)
				signal_handle_function(SIGINT);
			parse_command(cmd, envp);
			if (cmd->fd_in > 2)
				close(cmd->fd_in);
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

/*  check for redirections and open them
	do the dup2 stuff.
	check for how many pipes there are.
	until the second to last do the
	new pipex function with the cmd
	last cmd should be done with parse command
	probably also do a fork 
	(or maybe do the fork just before the parser) 
	maybe store the pid in the envp to use with kill
	in case of minishell in minishell stuff???
	and do a different signal handler depending on 
	what fork you are on.
	see the lexer tester for some stuff 
 */
void	parse_token_lst(t_token *lst, char **envp)
{
	t_token		*tmp;
	t_command	*cmd;
	int			pipe_cnt;

	pipe_cnt = 0;
	cmd = new_command(NULL);
	pipe_cnt = parse_redirection(lst, envp, cmd);
	tmp = lst;
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	parse_command_lst(tmp, envp, cmd, pipe_cnt);
	if (cmd->cmds)
		free_cmds(cmd);
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
