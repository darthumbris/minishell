/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/16 15:34:50 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dispatch.h"
#include "tokenizer.h"

static int	parse_redirection(t_token *lst, char **envp, t_command *cmd)
{
	t_token		*tmp;
	int			pipe_cnt;
	int			done;

	tmp = lst;
	pipe_cnt = 0;
	done = 0;
	while (tmp)
	{
		if (tmp->token_name[0] == '<')
			cmd->fd_in = redirect_parse(tmp, envp);
		else if (tmp->token_name[0] == '>')
			cmd->fd_out = redirect_parse(tmp, envp);
		else if (tmp->token_name[0] == '|')
			pipe_cnt++;
		else if (tmp->token_name[0] == 'h' && !done)
		{
			redirect_parse(tmp, envp);
			done = 1;
		}
		tmp = tmp->next;
	}
	return (pipe_cnt);
}

// //need to check first if the commands are valid?
// //NEED TO CHECK THE CMDS BEFORE THE FORKING!!!!!!!!!
// static void	parse_command_lst(t_token *tmp, char **envp, \
// 	t_command *cmd, int pipe_cnt)
// {
// 	int		temp_status;
// 	int		status;
// 	bool	valid;

// 	status = 0;
// 	valid = true;
// 	while (tmp)
// 	{
// 		if (tmp->token_name[0] == 'W')
// 		{
// 			if (cmd->cmds)
// 				free_cmd_args(cmd->cmds);
// 			cmd = create_cmd_lst(&tmp, cmd);
// 			if (ft_strcmp(cmd->cmds[0], "cat") != 0)
// 				valid = false;
// 		}
// 		if (pipe_cnt && cmd && cmd->cmds)
// 		{
// 			temp_status = new_pipex_multiple(cmd, envp);
// 			//printf("temp: %d\n", temp_status);
// 			if (temp_status == 2 || temp_status == 3)
// 				status = temp_status;
// 			pipe_cnt--;
// 		}
// 		else if (cmd && cmd->cmds)
// 		{
// 			dup2(cmd->fd_in, STDIN_FILENO);
// 			if (WIFEXITED(status) == 0 && status == 2)
// 			{
// 				//signal_handle_function(SIGINT);
// 				//exit(0);
// 			}
// 			if (WIFEXITED(status) == 0 && status == 3)
// 			{
// 				//exit(0);
// 				//signal_handle_function(SIGQUIT);
// 			}
// 			parse_command(cmd, envp);
// 		}
// 		if (tmp)
// 			tmp = tmp->next;
// 	}
// }

int	single_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	else
		parse_command(cmd, envp);
	waitpid(pid, &status, 0);
	return (status);
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
	t_command	*tmp_cmd;
	int			pipe_cnt;
	int			status;

	cmd = new_command(NULL);
	pipe_cnt = parse_redirection(lst, envp, cmd);
	tmp = lst;
	if (pipe_cnt == 0)
	{
		tmp_cmd = get_next_command(&lst);
		if (tmp_cmd)
		{
			tmp_cmd->fd_in = cmd->fd_in;
			tmp_cmd->fd_out = cmd->fd_out;
			status = single_command(tmp_cmd, envp);
			free_cmds(tmp_cmd);
		}
		//free_cmds(cmd);
	}
	else
		status = pipex_concurrent(lst, envp, pipe_cnt, cmd);
	// if (cmd->fd_in < 0 || cmd->fd_out < 0)
	// {
	// 	free_cmds(cmd);
	// 	exit(1);
	// }
	//printf("status: %d\n", status);
	if (cmd->cmds)
		free_cmds(cmd);
	//exit(0);
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
	//ft_putendl_fd("parse command", 2);
	//ft_putendl_fd(cmd->cmds[0], 2);
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
