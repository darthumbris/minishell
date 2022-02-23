/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:57:28 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/23 13:13:03 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dispatch.h"
#include "tokenizer.h"

// int	last_command(t_command *cmd, char **envp)
// {
// 	pid_t		pid;
// 	int			status = 0;

// 	ft_putendl_fd("what?", 2);
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("FORK");
// 		ft_putendl_fd("error", 2);
// 		return (-1);
// 	}
// 	else if (pid == 0)
// 		parse_command(cmd, envp);
// 	else
// 	{
// 		signal(SIGQUIT, SIG_IGN);
// 		signal(SIGINT, SIG_IGN);
// 		waitpid(pid, &status, 0);
// 		if (status == 2)
// 			signal_handle_function(SIGINT);
// 		if (status == 3)
// 			signal_handle_function(SIGQUIT);
// 	}
// 	return (status);
// }

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

void	check_redir_in(t_token **lst, char **envp, t_command *cmd);

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

//need to check first if the commands are valid?
//NEED TO CHECK THE CMDS BEFORE THE FORKING!!!!!!!!!
static void	parse_command_lst(t_token *tmp, char **envp, \
	t_command *cmd, int pipe_cnt)
{
	int		temp_status;
	int		status;

	status = 0;
	while (tmp)
	{
		if (tmp->token_name[0] == 'W')
		{
			free_cmd_args(cmd->cmds);
			cmd = create_cmd_lst(&tmp, cmd, envp);
		}
		check_redir_in(&tmp, envp, cmd);
		check_redir_out(&tmp, envp, cmd);
		if (pipe_cnt && cmd && cmd->cmds)
		{
			temp_status = new_pipex_multiple(cmd, envp);
			if (temp_status == 2 || temp_status == 3)
				status = temp_status;
			pipe_cnt--;
			free_cmd_args(cmd->cmds);
			cmd->cmds = NULL;
		}
		else if (cmd && cmd->cmds)
		{
			dup_and_close(&(cmd->fd_out), STDOUT_FILENO);
			parse_command(cmd, envp);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return ;
	exit(0);
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
	t_command	**cmds;
	int			i;

	cmd = new_command(NULL);
	pipe_cnt = count_pipes(lst, envp);
	tmp = lst;
	if (!cmd)
		parse_command_lst(tmp, envp, cmd, pipe_cnt);
	cmds = get_commands(tmp, pipe_cnt + 1, envp);
	i = 0;
	// while (cmds[i])
	// {
	// 	fprintf(stderr, "cmd[%d]: %s\n", i, cmds[i]->cmds[0]);
	// 	if (cmds[i]->cmds[1])
	// 		fprintf(stderr, "cmd[%d]: %s\n", i, cmds[i]->cmds[1]);
	// 	fprintf(stderr, "fd_in[%d]: %d\n", i, cmds[i]->fd_in);
	// 	fprintf(stderr, "fd_out[%d]: %d\n", i, cmds[i]->fd_out);
	// 	i++;
	// }
	if (cmd->cmds)
		free_cmds(cmd);
	exit(0);
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
