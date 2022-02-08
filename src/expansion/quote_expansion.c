/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 10:31:50 by abba          #+#    #+#                 */
/*   Updated: 2022/02/08 10:48:34 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*quote_expansion(t_token *lst)
{
	char	*value;
	t_token	*tmp;

	tmp = lst;
	lst = lst->next;
	while (lst)
	{
		if (ft_strcmp(lst->token_name, "W") || ft_strcmp(lst->token_name, "F"))
		{
			value = check_for_expans(lst->token_value);
			free(lst->token_value);
			lst->token_value = value;
		}
		lst = lst->next;
	}
	return (tmp);
}
