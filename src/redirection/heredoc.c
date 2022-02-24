/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:11:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 16:44:52 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

static int	count_heredocs(t_token *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		if (ft_strcmp(lst->token_name, "|") == 0)
			break ;
		if (ft_strcmp(lst->token_name, "h") == 0)
			len++;
		lst = lst->next;
	}
	return (len);
}

static char	**get_delimiter(t_token *lst)
{
	char	**delimiter;
	int		i;

	i = 0;
	delimiter = ft_calloc(count_heredocs(lst) + 1, sizeof(char *));
	if (!delimiter)
		return (NULL);
	while (lst)
	{
		if (ft_strcmp(lst->token_name, "h") == 0)
		{
			lst = lst->next;
			delimiter[i] = lst->token_value;
			i++;
		}
		lst = lst->next;
	}
	return (delimiter);
}

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

static int	delimiter_len(char **delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
		i++;
	return (i);
}

/*
 * This function should handle the
 * << redirect and make an heredoc
 * that properly closes with the
 * input name (EOF or another word etc.)
 * than should write everything correctly
 * to the fd_outpout.
 */
int	heredoc_function(t_token *lst, char **envp)
{
	char	**delimiter;
	char	*line;
	int		fd[2];
	int		i;

	i = 0;
	delimiter = get_delimiter(lst);
	while (1)
	{
		rl_on_new_line();
		line = readline("> ");
		if (delimiter_len(delimiter) == 1)
		{
			pipe(fd);
			while (line && ft_strcmp(line, *delimiter) != 0)
			{
				if (line && ft_strcmp(line, *delimiter) == 0)
					break ;
				line = expand_input(line, envp);
				write(fd[0], line, ft_strlen(line));
				write(fd[0], "\n", 1);
				free(line);
				rl_on_new_line();
				line = readline("> ");
				if (!line)
					ft_putstr_fd("> \x1b[1T", 0);
			}
			free(delimiter);
			free(line);
			close(fd[0]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			return (0);
		}
		else if (ft_strcmp(line, delimiter[i]) == 0)
		{
			delimiter++;
			i++;
		}
		free(line);
	}
	return (-1);
}
