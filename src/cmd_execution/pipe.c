/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 10:49:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/23 16:30:05 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipe.h"

int	err_msg(char *msg, int ret)
{
	perror(msg);
	return (ret);
}

int	new_pipex_multiple(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		err_msg("FORK", 1);
	else if (pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		dup_and_close(&(cmd->fd_out), STDOUT_FILENO);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		//close(pipe_fd[0]);
		waitpid(pid, &status, 0);
	}
	else
	{
		dup_and_close(&(cmd->fd_in), STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		//close(pipe_fd[1]);
		parse_command(cmd, envp);
	}
	set_return_value(envp, WEXITSTATUS(status));
	return (status);
}

static int	count_cmd_args_lst(t_token *lst)
{
	t_token	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		if (tmp->token_name[0] == '|')
			break ;
		if (tmp->token_name[0] == 'W')
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_command	*get_next_command(t_token **lst, char **envp, int fd_in, int fd_out)
{
	char		**cmds;
	int			len;
	int			i;
	t_command	*cmd;

	while ((*lst))
	{
		if ((*lst)->token_name[0] == '>')
			fd_out = redirect_parse((*lst), envp);
		if (((*lst)->token_name[0] == '<' || (*lst)->token_name[0] == 'h'))
			fd_in = redirect_parse((*lst), envp);
		if ((*lst)->token_name[0] == 'W')
		{
			cmd = new_command(NULL);
			cmd->fd_in = fd_in;
			cmd->fd_out = fd_out;
			len = count_cmd_args_lst((*lst));
			cmds = ft_calloc(len + 1, sizeof(char *));
			i = 0;
			while (i < len)
			{
				if ((*lst)->token_name[0] == 'W')
					cmds[i++] = ft_strdup((*lst)->token_value);
				if ((*lst)->token_name[0] == '>' && cmd->fd_out != -1)
				{
					dup_and_close(&(cmd->fd_out), STDOUT_FILENO);
					cmd->fd_out = redirect_parse((*lst), envp);
				}
				else if (((*lst)->token_name[0] == '<' || \
				(*lst)->token_name[0] == 'h') && cmd->fd_in != -1)
				{
					dup_and_close(&(cmd->fd_in), STDIN_FILENO);
					cmd->fd_in = redirect_parse((*lst), envp);
				}
				(*lst) = (*lst)->next;
			}
			cmd->cmds = cmds;
			return (cmd);
		}
		if ((*lst))
			(*lst) = (*lst)->next;
	}
	return (NULL);
}

t_command	**get_commands(t_token *lst, int cmd_cnt, char **envp)
{
	t_command	**cmds;
	t_token		*tmp;
	int			i;

	tmp = lst;
	cmds = ft_calloc(cmd_cnt + 1, sizeof(t_command *));
	i = 0;
	while (i < cmd_cnt)
	{
		cmds[i] = get_next_command(&tmp, envp, 0, 1);
		check_redir_in(&tmp, envp, cmds[i]);
		check_redir_out(&tmp, envp, cmds[i]);
		i++;
	}
	return (cmds);
}

void	redirect(t_command *cmd, int pid)
{
	if (pid == 0 && cmd)
	{
		if (cmd->fd_in > 2)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->fd_out > 2)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
	}
}

void	piper(t_command **cmds, char **envp, int pipes)
{
	int		i;
	//t_pipe	piper;
	int		fd[pipes][2];
	int		status;
	pid_t	pid;
	pid_t	*pid_save;
	int		j;

	//set_pipestruct(&piper, pipes);
	pid_save = ft_calloc(pipes, sizeof(pid_t));
	i = 0;
	while (i < pipes)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("PIPE");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < pipes + 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("FORK");
			exit(1);
		}
		if (pid == 0)
		{
			if (i == 0)
				dup2(fd[i][1], STDOUT_FILENO);
			if (i != 0 && i != pipes)
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				dup2(fd[i][1], STDOUT_FILENO);
			}
			if (i == pipes)
				dup2(fd[i - 1][0], STDIN_FILENO);
			j = 0;
			while (j < pipes)
			{
				close(fd[j][0]);
				close(fd[j][1]);
				j++;
			}
			if (!cmds[i])
				exit(1);
			redirect(cmds[i], pid);
			parse_command(cmds[i], envp);
			exit(1);
		}
		else
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, SIG_IGN);
			if (i < pipes)
				pid_save[i] = pid;
			if (i == pipes)
			{
				for (int l = 0; l < pipes; l++)
				{
					close(fd[l][0]);
					close(fd[l][1]);
				}
				for (int k = 0; k < pipes; k++)
				{
					waitpid(pid_save[k], &status, 0);
				}
				waitpid(pid, NULL, 0);
				if (status == 3)
					signal_handle_function(SIGQUIT);
				if (status == 2)
					signal_handle_function(SIGINT);
				exit(status);
			}
		}
		i++;
	}
}
