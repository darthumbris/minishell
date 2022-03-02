/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 11:15:43 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/02 10:51:19 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

bool	check_heredoc(t_token **lst, t_command *cmd)
{
	if ((*lst) && (*lst)->token_name[0] == 'h')
	{
		if (cmd && !(cmd->delimiter))
			cmd->delimiter = get_delimiter((*lst));
		while ((*lst))
		{
			if ((*lst) && (*lst)->token_name[0] == '|')
				break ;
			if ((*lst))
				(*lst) = (*lst)->next;
		}
		return (true);
	}
	return (false);
}

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

char	**get_delimiter(t_token *lst)
{
	char	**delimiter;
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = lst;
	delimiter = ft_calloc(count_heredocs(tmp) + 1, sizeof(char *));
	if (!delimiter)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->token_name, "|") == 0)
			break ;
		if (ft_strcmp(tmp->token_name, "h") == 0)
		{
			tmp = tmp->next;
			delimiter[i] = ft_strdup(tmp->token_value);
			i++;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (delimiter);
}

void	free_delimiter(char **delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		free(delimiter[i]);
		delimiter[i] = NULL;
		i++;
	}
	free(delimiter);
	delimiter = NULL;
}
