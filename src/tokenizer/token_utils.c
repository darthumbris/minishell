/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 15:05:33 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/02 15:15:53 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	init_check(t_check *check)
{
	check->single_quote = false;
	check->double_quotes = false;
	check->count_s = 0;
	check->count_d = 0;
	check->len = 1;
	check->position = 0;
}

void	single_quote(t_check *check)
{
	check->count_s++;
	if (check->count_s % 2 == 0)
		check->single_quote = false;
	else
		check->single_quote = true;
}

void	double_quotes(t_check *check)
{
	check->count_d++;
	if (check->count_d % 2 == 0)
		check->single_quote = false;
	else
		check->single_quote = true;
}

void	fill_str(char	*str, int *j, int i)
{
	str[*j] = str[i];
	(*j)++;
}

char	*remove_white_spaces(char *str, t_check *check)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quote(check);
		if (str[i] == '\"')
			double_quotes(check);
		if (str[i] != ' ' && !check->single_quote && !check->double_quotes)
			fill_str(str, &j, i);
		else if (str[i] == ' ' && str[i + 1] != ' ' && !check->single_quote \
			&& !check->double_quotes && str[i + 1] != '\0')
		{
			fill_str(str, &j, i);
			check->len++;
		}
		else if (check->single_quote || check->double_quotes)
			fill_str(str, &j, i);
		i++;
	}
	str[j] = '\0';
	return (str);
}
