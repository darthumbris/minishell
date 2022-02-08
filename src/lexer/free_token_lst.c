/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_token_lst.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 14:13:58 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/08 10:48:58 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
 * This function will free the token list.
 */
void	free_token_lst(t_token **lst)
{
	t_token	*tmp;

	tmp = *lst;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->token_value);
		free(*lst);
		*lst = tmp;
	}
}
