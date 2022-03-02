/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 14:33:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/02 11:02:08 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

void	heredoc_pipe_cmd(char *line, t_command *cmd, char **envp, int i)
{
	int		fd[2];

	pipe(fd);
	while (line && ft_strcmp(line, cmd->delimiter[i]) != 0)
	{
		if (line && ft_strcmp(line, cmd->delimiter[i]) == 0)
			break ;
		if (cmd->fd_in == 0)
		{
			line = expand_input(line, envp);
			ft_putendl_fd(line, fd[1]);
		}
		free(line);
		rl_on_new_line();
		line = readline("> ");
		if (!line)
			ft_putstr_fd("> \x1b[1T", 1);
	}
	free(line);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

//HANDLE SIGNAL!!!!
void	heredoc_with_command(t_command *cmd, char **envp)
{
	char	*line;
	int		i;

	i = 0;
	while (true)
	{
		rl_on_new_line();
		line = readline("> ");
		if (cmd->heredocs - i == 1)
			return (heredoc_pipe_cmd(line, cmd, envp, i));
		else if (ft_strcmp(line, cmd->delimiter[i]) == 0)
			i++;
		free(line);
	}
}
