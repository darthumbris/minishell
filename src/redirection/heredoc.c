/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:11:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/28 17:01:47 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

static bool	need_expansion(char *str, int *i)
{
	*i = 0;
	while (str[*i])
	{
		if (str[*i] == '$' && str[*i + 1] != ' ')
			return (true);
		(*i)++;
	}
	return (false);
}

char	*expand_input(char *line, char **envp)
{
	char	*str;
	int		i;
	char	*tmp;

	if (need_expansion(line, &i))
	{
		str = ft_strdup(line);
		str[i] = 0;
		line = expand_env_variable(line + i + 1, envp);
		tmp = str;
		str = ft_strjoin(tmp, line);
		free(tmp);
	}
	else
		str = ft_strdup(line);
	free(line);
	return (str);
}

static int	delimiter_len(char **delimiter, int pos)
{
	int	i;

	i = pos;
	while (delimiter[i])
		i++;
	return (i - pos);
}

static char	**free_delimiter(char **delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		fprintf(stderr, "del: %s\n", delimiter[i]);
		free(delimiter[i]);
		delimiter[i] = NULL;
		i++;
	}
	free(delimiter);
	delimiter = NULL;
	return (NULL);
}

/*
 * This function should handle the
 * << redirect and make an heredoc
 * that properly closes with the
 * input name (EOF or another word etc.)
 * than should write everything correctly
 * to the fd_outpout.
 */
//HANDLE SIGNAL!!!!
//HANDLE LEAK WHEN CTRL-D
int	heredoc_function(t_token *lst, char **envp)
{
	char	**delimiter;
	char	*line;
	int		fd[2];
	int		i;

	i = 0;
	delimiter = get_delimiter(lst);
	while (true)
	{
		rl_on_new_line();
		line = readline("> ");
		if (delimiter_len(delimiter, i) == 1)
		{
			pipe(fd);
			while (line && ft_strcmp(line, delimiter[i]) != 0)
			{
				if (line && ft_strcmp(line, delimiter[i]) == 0)
					break ;
				line = expand_input(line, envp);
				ft_putendl_fd(line, fd[1]);
				free(line);
				rl_on_new_line();
				line = readline("> ");
				if (!line)
					ft_putstr_fd("> \x1b[1T", 1);
			}
			free_delimiter(delimiter);
			free(line);
			close(fd[0]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			return (0);
		}
		else if (ft_strcmp(line, delimiter[i]) == 0)
			i++;
		free(line);
	}
	return (-1);
}

//HANDLE SIGNAL!!!!
void	heredoc_with_command(t_command *cmd, char **envp)
{
	char	*line;
	int		i;
	int		fd[2];

	i = 0;
	while (true)
	{
		rl_on_new_line();
		line = readline("> ");
		if (cmd->heredocs - i == 1)
		{
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
			return ;
		}
		else if (ft_strcmp(line, cmd->delimiter[i]) == 0)
			i++;
		free(line);
	}
}

// int	heredoc_in_pipe(t_command *cmd, char **envp, int fd_out, int fd_in)
// {
// 	char	*line;
// 	int		i;
// 	//int		fd[2];

// 	i = 0;
// 	(void)fd_in;
// 	(void)fd_out;
// 	//pipe(fd);
// 	//dup2(fd_out, fd[1]);
// 	//close(fd_out);
// 	while (true)
// 	{
// 		rl_on_new_line();
// 		line = readline("> ");
// 		if (cmd->heredocs - i == 1)
// 		{
// 			while (line && ft_strcmp(line, cmd->delimiter[i]) != 0)
// 			{
// 				if (line && ft_strcmp(line, cmd->delimiter[i]) == 0)
// 					break ;
// 				if (cmd->fd_in == 0)
// 				{
// 					line = expand_input(line, envp);
// 					ft_putendl_fd(line, fd_out);
// 				}
// 				free(line);
// 				rl_on_new_line();
// 				line = readline("> ");
// 				rl_redisplay();
// 				if (!line)
// 					ft_putstr_fd("> \x1b[1T", 1);
// 			}
// 			free(line);
// 			// if (fd_in)
// 			// {
// 			// 	dup2(fd[0], STDIN_FILENO);
// 			// 	close(fd[0]);
// 			// 	//close(fd[1]);
// 			// }
// 			// //close(fd[1]);
// 			// close(fd[0]);
// 			close(fd_in);
// 			//close(fd_out);
// 			return (0);
// 		}
// 		else if (ft_strcmp(line, cmd->delimiter[i]) == 0)
// 			i++;
// 		free(line);
// 	}
// 	return (-1);
// }
