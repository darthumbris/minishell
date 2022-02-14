/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 12:56:39 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/11 10:31:59 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

/*
 * This function will open the file for input and set the 
 * fds for the cmd struct.
 * it will also give an error if the filedescriptor
 * is bad.
 */
static int	redirect_input(t_token *lst, char **envp)
{
	int	fd_in;

	fd_in = 0;
	if (lst && lst->next)
	{
		fd_in = open(lst->next->token_value, O_RDONLY);
		if (fd_in < 0)
		{
			perror(lst->next->token_value);
			set_return_value(envp, 1);
		}
	}
	return (fd_in);
}

/*
 * This function will open the file for output and set the 
 * fds for the cmd struct.
 * it will also give an error if the filedescriptor
 * is bad.
 * O_TRUNC is so it makes an empty file if it already exists.
 */
static int	redirect_output(t_token *lst, int append, char **envp)
{
	int	fd_out;

	fd_out = 1;
	if (lst && lst->next)
	{
		if (append == 2)
			fd_out = open
				(lst->next->token_value, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd_out = open
				(lst->next->token_value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd_out < 0)
		{
			perror(lst->next->token_value);
			set_return_value(envp, 1);
		}
	}
	return (fd_out);
}

/*
 * This function will check what kind of redirect it
 * is and than will go to either input, heredoc
 * or output function and will return
 * the fd they create. or -1 if it fails.
 */
int	redirect_parse(t_token *lst, char **envp)
{
	int	len;
	int	i;

	if (lst)
	{
		i = 0;
		while (ft_isdigit(lst->token_value[i]))
		i++;
		len = i;
		while (lst->token_value[i] == lst->token_value[len])
			i++;
		if (lst->token_name[0] == '<')
		{
			if ((i - len) == 1)
				return (redirect_input(lst, envp));
			return (heredoc_function());
		}
		return (redirect_output(lst, i - len, envp));
	}
	return (-1);
}

/*
 * This function will check the [n]> and [n]<
 * redirections for the n value if it is a valid
 * fd to redirect.
 * need to change this function so it actually
 * sets the fd to the input (or 0 or 1 if it fails)
 */
int	redirect_fd(t_token	*lst)
{
	char	*red;

	red = lst->token_value;
	if (!ft_isdigit(red[0]) && lst->token_name[0] == '>')
		return (1);
	if (!ft_isdigit(red[0]) && lst->token_name[0] == '<')
		return (0);
	if (ft_atol(red) < INT_MAX && ft_atoi(red) < 255 && \
		fstat(ft_atoi(red), NULL) != -1)
		return (ft_atoi(red));
	else if (ft_atol(red) > INT_MAX)
		ft_putendl_fd("minishell: file descriptor out of range: \
	 		Bad file descriptor", 2);
	else if (ft_atoi(red) > 255 || fstat(ft_atoi(red), NULL) == -1)
		printf("minishell: %d Bad file descriptor\n", \
			ft_atoi(red));
	if (lst->token_name[0] == '>')
		return (1);
	if (lst->token_name[0] == '<')
		return (0);
	return (-1);
}
