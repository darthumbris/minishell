/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lenght_count.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 12:47:36 by abba          #+#    #+#                 */
/*   Updated: 2022/02/07 15:12:12 by abba          ########   odam.nl         */
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
