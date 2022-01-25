/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:06:50 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:07:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*src_str;
	char		*dst_str;

	src_str = src;
	dst_str = dst;
	if (src == NULL && dst == NULL)
		return (dst);
	while (n)
	{
		*dst_str = *src_str;
		dst_str++;
		src_str++;
		n--;
	}
	return (dst);
}
