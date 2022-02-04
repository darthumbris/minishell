/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:45:46 by abba          #+#    #+#                 */
/*   Updated: 2022/02/02 15:17:53 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

char	*str_copy(char *str, int end, int start)
{
	char	*output;
	int		i;

	i = 0;
	if (str[end + 1] == '\0')
		end++;
	output = ft_calloc(end - start + 1, sizeof(char *));
	if (!output)
		return (NULL);
	while (start < end)
	{
		output[i] = str[start];
		i++;
		start++;
	}
	return (output);
}

char	**split_output(char *str, t_check *check, int len)
{
	char	**output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	output = ft_calloc(len + 1, sizeof(char *));
	if (!output)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			single_quote(check);
		if (str[i] == '\"')
			double_quotes(check);
		else if ((str[i] == ' ' && !check->single_quote \
			&& !check->double_quotes) || (str[i + 1] == '\0'))
		{
			output[j] = str_copy(str, i, check->position);
			check->position = i + 1;
			j++;
		}
		i++;
	}	
	return (output);
}

char	**tokenizer(char *input)
{
	t_check	check;
	char	**tokens;
	int		len;

	init_check(&check);
	input = ft_whitespaces(input);
	input = remove_white_spaces(input, &check);
	len = check.len;
	init_check(&check);
	tokens = split_output(input, &check, len);
	return (tokens);
}
