/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:06:19 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:06:19 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	length_nbr(long int n)
{
	int		len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
	{
		n = 0 - n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nbr;

	nbr = n;
	len = length_nbr(n);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = 0 - nbr;
	}
	while (nbr > 0)
	{
		str[len - 1] = '0' + (nbr % 10);
		nbr = nbr / 10;
		len--;
	}
	return (str);
}
