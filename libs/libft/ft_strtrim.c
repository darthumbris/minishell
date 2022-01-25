/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:07:26 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:07:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_b(char const *s1, char const *set, int i, int j)
{
	int	temp;

	temp = 0;
	while (s1[j])
	{
		while (set[i])
		{
			if (s1[j] == set[i])
			{
				temp = 1;
				break ;
			}
			i++;
		}
		if (temp)
		{
			i = 0;
			temp = 0;
		}
		else
			break ;
		j++;
	}
	return (j);
}

static int	ft_len_e(char const *s1, char const *set, int i, int j)
{
	int	temp;

	temp = 0;
	while (j > 0)
	{
		while (set[i])
		{
			if (s1[j] == set[i])
			{
				temp = 1;
				break ;
			}
			i++;
		}
		if (temp)
		{
			i = 0;
			temp = 0;
		}
		else
			break ;
		j--;
	}
	return (j + 1);
}

static char	*ft_strtrim_if(char const *s1, char const *set, int len_b, int len)
{
	int		i;
	int		len_e;
	char	*trimmed;

	i = len_b;
	len_e = len - ft_len_e(s1, set, 0, (len - 1));
	trimmed = malloc(sizeof(char) * (len - len_b - len_e + 1));
	if (trimmed == 0)
		return (NULL);
	while (i < (len - len_e))
	{
		trimmed[i - len_b] = s1[i];
		i++;
	}
	trimmed[i - len_b] = '\0';
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		len_b;
	int		len;

	if (s1 && set)
	{
		len = ft_strlen(s1);
		len_b = ft_len_b(s1, set, 0, 0);
		if (len_b != len)
			trimmed = ft_strtrim_if(s1, set, len_b, len);
		else
			trimmed = ft_calloc(1, 1);
		return (trimmed);
	}
	return (NULL);
}
