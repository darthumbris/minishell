/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:05:57 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:05:58 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;
	int		i;

	i = 0;
	temp = malloc(count * size);
	if (temp)
		ft_bzero(temp, count * size);
	return (temp);
}
