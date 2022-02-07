/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lenght_count.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 12:47:36 by abba          #+#    #+#                 */
/*   Updated: 2022/02/07 12:47:39 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "quotes.h"

int	ft_count(char *str, int i, char c)
{
	int	len;

	len = 0;
	while (str[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}


int	ft_count1(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != '\'' )
	{
		if (str[i] == '"')
			break ;
		len++;
		i++;
	}
	return (len);
}

//this function return the len of list so we can get the exact size to malloc
int lstsize(t_token *lst)
{
    int len;

    len = 0;
    while(lst)
    {
        len++;
        lst = lst->next;
    }
    return (len);
}