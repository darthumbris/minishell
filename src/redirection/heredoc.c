/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:11:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/23 16:28:42 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

/*
 * This function should handle the
 * << redirect and make an heredoc
 * that properly closes with the
 * input name (EOF or another word etc.)
 * than should write everything correctly
 * to the fd_outpout.
 */

int	count_len(t_token *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		if (ft_strcmp(lst->token_name, "h"))
			len++;
		lst = lst->next;
	}
	return (len);
}

char	**get_end(t_token *lst)
{
	char	**end;
	int		i;

	i = 0;
	end = ft_calloc(count_len(lst) + 1, sizeof(char *));
	if (!end)
		return (NULL);
	while (lst)
	{
		if (ft_strcmp(lst->token_name, "h") == 0)
		{
			lst = lst->next;
			end[i] = lst->token_value;
			i++;
		}
		lst = lst->next;
	}
	return (end);
}

char	*rm_last_line(char *line)
{
	int	i;

	i = strlen(line) - 1;
	// if (line[i] == '\n')
	// 	line[i] = '\0';
	return (line);
}

bool	need_exp(char *str, int *i)
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

char	*test(char *line, char **envp)
{
	char	*str;
	int		i;

	if (need_exp(line, &i))
	{
		str = ft_strdup(line);
		str[i] = 0;
		line = expand_env_variable(line + i + 1, envp);
		str = ft_strjoin(str, line);
	}
	else
		str = line;
	return (str);
}

int	end_len(char **end)
{
	int	i;

	i = 0;
	while (end[i])
		i++;
	return (i);
}

int	heredoc_function(t_token *lst, char **envp)
{
	char	**end;
	char	*line;
	int		fd[2];
	int		i;

	i = 0;
	end = get_end(lst);
	while (1)
	{
		line = ft_strdup("");
		rl_on_new_line();
		line = readline("> ");
		if (end_len(end) == 1)
		{
			pipe(fd);
			while (line && ft_strcmp(line, *end) != 0)
			{
				if (line && ft_strcmp(line, *end) == 0)
					break ;
				line = test(line, envp);
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
				free(line);
				rl_on_new_line();
				line = readline("> ");
			}
			free(*end);
			free(line);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			return (0);
		}
		else if (ft_strcmp(line, end[i]) == 0)
		{
			free(*end);
			end++;
			i++;
		}
		free(line);
	}
	return (-1);
}
