/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 11:37:57 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/02 11:00:44 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*lexer_lst(char *input, char **envp)
{
	t_token	*lst;
	t_token	*tmp;

	lst = lexer(input);
	tmp = lst;
	while (tmp)
	{
		if ((tmp->token_name[0] == 'W' || tmp->token_name[0] == 'F') && \
			ft_strchr(tmp->token_value, '$'))
			check_for_env_expansion(&(tmp->token_value), envp, tmp);
		tmp = tmp->next;
	}
	lst = quote_expansion(lst);
	if (!evaluator(lst))
		free_token_lst(&lst);
	return (lst);
}
