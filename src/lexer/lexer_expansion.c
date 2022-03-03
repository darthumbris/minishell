/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 11:37:57 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/03 15:05:54 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdio.h>

static void	removing_token(t_token	*prev, t_token	*tmp)
{
	prev->next = tmp->next;
	free(tmp);
	tmp = prev;
}

t_token	*lexer_lst(char *input, char **envp)
{
	t_token	*lst;
	t_token	*tmp;
	t_token	*prev;

	lst = lexer(input);
	tmp = lst;
	prev = tmp;
	while (tmp)
	{
		if ((tmp->token_name[0] == 'W' || tmp->token_name[0] == 'F') && \
			ft_strchr(tmp->token_value, '$'))
			check_for_env_expansion(&(tmp->token_value), envp, tmp);
		if (tmp->token_value == NULL)
			removing_token(prev, tmp);
		if (tmp)
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	lst = quote_expansion(lst);
	if (!evaluator(lst))
		free_token_lst(&lst);
	return (lst);
}
