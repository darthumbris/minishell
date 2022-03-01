/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:05:57 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/01 16:00:53 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	temp = malloc(count * size);
	if (temp)
		ft_bzero(temp, count * size);
	return (temp);
}
