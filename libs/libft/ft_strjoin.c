/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:07:10 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/14 12:34:20 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	joined = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (joined == 0)
		return (NULL);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		joined[i] = *s2;
		i++;
		s2++;
	}
	return (joined);
}
