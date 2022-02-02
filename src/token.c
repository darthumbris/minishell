/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:45:46 by abba          #+#    #+#                 */
/*   Updated: 2022/02/02 14:21:40 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <stdlib.h>

char	**envp_duplicate(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(1024, sizeof(char *));
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (tmp);
}

typedef struct s_check
{
	int		count_s;
	int		count_d;
	int		len;
	int		position;
	bool	single_quote;
	bool	double_quotes;
}		t_check;

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

char *remove_white_spaces(char *str, t_check *check)
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

char	**split_output(char *str, t_check *check)
{
	char	**output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	output = ft_calloc(check->len + 1, sizeof(char *));
	if (!output)
		return (NULL);
	init_check(check);
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

void	tokenizer(char *output)
{
	t_check	check;
	char	**test;
	int		i;

	i = 0;
	init_check(&check);
	output = remove_white_spaces(output, &check);
	test = split_output(output, &check);
	while (test[i])
	{
		printf("test: <%s>\n", test[i]);
		free(test[i]);
		i++;
	}
	free(test);
}

// out = cd "hello"yoou '    d' hello
// free
