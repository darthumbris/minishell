/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 10:31:50 by abba          #+#    #+#                 */
/*   Updated: 2022/02/07 12:48:15 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "quotes.h"

t_token *expansion(t_token *lst)
{
    char	**value;
    int		len;
    t_token	*tmp;
	
	lst = lst->next;
    len = lstsize(lst);
    value = ft_calloc(len + 1, sizeof(char *));
    if (!value)
        return (0);
    len = 0;
	while(lst)
	{
        tmp = lst->next;
        value[len] = check(lst->token_value);
        len++;
        free(lst);
		lst = tmp;
	}
    value[len] = NULL;
	len = 0;
	while (value[len])
	{
		free(value[len]);
		len++;
	}
	free(value);
    return (lst);
}
