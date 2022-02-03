/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_lst.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:02:26 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/03 16:15:49 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*new_token(char *token_name, char *token_value)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->token_name = token_name;
	new->token_value = token_value;
	new->next = NULL;
	return (new);
}

static t_token	*get_last_token(t_token *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	add_new_token(t_token **lst, t_token *new)
{
	t_token	*lst_last;

	if (lst)
	{
		if (*lst)
		{
			lst_last = get_last_token(*lst);
			lst_last->next = new;
		}
		else
			*lst = new;
	}
}
