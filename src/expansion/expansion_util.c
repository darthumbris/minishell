/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_util.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 12:44:19 by abba          #+#    #+#                 */
/*   Updated: 2022/02/07 15:07:51 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "quotes.h"

static char	*single_function(char *input, int *i)
{
	int			j;
	char		*tmp;

	(*i)++;
	j = 0;
	tmp = ft_calloc(ft_count(input, *i, '\'') + 1, sizeof(char));
	if (!tmp)
		return (0);
	while (input[*i] && input[*i] != '\'')
	{
		tmp[j] = input[*i];
		(*i)++;
		j++;
	}
	return (tmp);
}

static char	*double_function(char *input, int *i)
{
	int			j;
	char		*tmp;

	(*i)++;
	j = 0;
	tmp = ft_calloc(ft_count(input, *i, '\"') + 1, sizeof(char));
	if (!tmp)
		return (0);
	while (input[*i] && input[*i] != '\"')
	{
		tmp[j] = input[*i];
		(*i)++;
		j++;
	}
	return (tmp);
}

static char	*normal_function(char *input, int *i)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_calloc(ft_count1(input, *i) + 1, sizeof(char));
	if (!tmp)
		return (0);
	while (input[*i] && input[*i] != '\'')
	{
		if (input[*i] == '"')
			break ;
		tmp[j] = input[*i];
		(*i)++;
		j++;
	}
	(*i)--;
	return (tmp);
}

char	*check(char *input)
{
	int	i;
	char						*tmp;
	const t_quote				function[] = {
		{'\'', &single_function},
		{'"', &double_function},
		{' ', &normal_function},
		{0, NULL}
	};

	i = 0;
	tmp = ft_strdup("");
	while (input[i])
	{
		if (input[i] == function[0].quote)
			tmp = ft_strjoin(tmp, function[0].t_function_pointer(input, &i));
		else if (input[i] == function[1].quote)
			tmp = ft_strjoin(tmp, function[1].t_function_pointer(input, &i));
		else
			tmp = ft_strjoin(tmp, function[2].t_function_pointer(input, &i));
		i++;
	}
	return (tmp);
}
