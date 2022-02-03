/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:01:40 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/03 16:58:56 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	move_through_quotes(char *input, int i)
{
	int	start;

	start = i;
	i++;
	while (input[i] && input[i] != input[start])
		i++;
	return (i);
}

int	move_through_spaces(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}

int	is_valid_fd_redirect(char *input, int start, int end)
{
	if (end == start)
		return (0);
	while (input[start] && start < end)
	{
		if (!ft_isdigit(input[start]))
			return (0);
		start++;
	}
	return (1);
}
