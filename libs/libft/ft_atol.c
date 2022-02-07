/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 10:12:08 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/07 10:12:46 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *str)
{
	long long	nbr;
	int			min;

	nbr = 0;
	min = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			min = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			break ;
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (nbr * min);
}