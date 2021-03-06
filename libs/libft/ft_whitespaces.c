/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 18:43:41 by abba          #+#    #+#                 */
/*   Updated: 2022/01/26 18:45:57 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_whitespaces(char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\n' || \
			*s == '\v' || *s == '\f' || *s == '\r')
		s++;
	return (s);
}
