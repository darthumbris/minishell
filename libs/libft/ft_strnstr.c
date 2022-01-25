/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:07:22 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:07:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	ndl_len;
	size_t	n;

	ndl_len = ft_strlen(needle);
	n = len - ndl_len;
	i = 0;
	if (ndl_len == 0 || needle == NULL)
		return ((char *)haystack);
	if (ndl_len > ft_strlen(haystack) || len == 0)
		return (NULL);
	while (i <= n)
	{
		if (haystack[0] == needle[0])
		{
			if (ft_strncmp(haystack, needle, ndl_len) == 0)
				return ((char *)haystack);
		}
		haystack++;
		i++;
	}
	return (NULL);
}
