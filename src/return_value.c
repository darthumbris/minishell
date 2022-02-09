/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   return_value.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:01:43 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/09 13:03:18 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_return_value(char **envp, int nbr)
{
	if (envp)
	{
		free(envp[0]);
		envp[0] = ft_itoa(nbr);
	}
}
