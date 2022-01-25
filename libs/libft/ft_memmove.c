/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:06:51 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:07:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*src_temp;
	char		*dst_temp;

	src_temp = src;
	dst_temp = dst;
	if (src == NULL && dst == NULL)
		return (dst);
	if (src_temp < dst_temp)
	{
		while (len)
		{
			len--;
			dst_temp[len] = src_temp[len];
		}
	}
	else
		ft_memcpy(dst_temp, src_temp, len);
	return (dst);
}
