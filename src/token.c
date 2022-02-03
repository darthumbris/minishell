/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:45:46 by abba          #+#    #+#                 */
/*   Updated: 2022/02/03 20:52:44 by abba          ########   odam.nl         */
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
	int count_s;
	int	count_d;
	int	len;
	int	position;
	bool single_quote;
	bool double_quotes;
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
		else if (str[i] == ' ' && str[i + 1] != ' ' && !check->single_quote\
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
	return str;
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

int	quote_count(char *str)
{
	int len;
	int	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			len++;
		i++;
	}
	return (len);
}


// string =  echo "hello 'ho  '   " f


// void	ft_test(char **output, char *str, int *j)
// {
// 	int		i;
// 	int		k;
// 	int		len;
// 	char	*quote;
 
// 	i = 0;
// 	k = 0;
// 	len = quote_count(str);
// 	quote = ft_calloc(len + 1, sizeof(char));
// 	if (!quote)
// 		return ;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '\"') // TO DOO TOMMMOROW FINISH EXPANSION PART echo hello " 'yoou'"   
// 		{
// 			quote[k] = str[i];
// 			k++;
// 		}
// 	}
	
// }

// char	*expansion(char **test)
// {
// 	int	i;
// 	int	j;
// 	char	*output;

// 	i = 0;
// 	j = 0;
// 	while (test[i])
// 	{
// 		ft_test(&output, test[i], &
// 		j);
// 		i++;
// 	}
// }

typedef struct s_quote
{
	char	quote;
	char	*(*t_function_pointer)(char *input, int *i);
}			t_quote;

int	ft_count(char *str, int i, char c)
{
	int	len;

	len = 0;
	while (str[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

char	*single_function(char *input, int *i)
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

char	*double_function(char *input, int *i)
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

int	ft_count1(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != '\'' )
	{
		if (str[i] == '"')
			break ;
		len++;
		i++;
	}
	return (len);
}

char	*normal_function(char *input, int *i)
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

char	*state_macchine(char *output)
{
	int							i;
	char						*str;
	const t_quote				function[] = {
		{'\'', &single_function},
		{'"', &double_function},
		{' ', &normal_function},
		{0, NULL}
	};
	
	i = 0;
	str = ft_strdup("");
	while(output[i])
	{
		if (output[i] == function[0].quote)
			str = ft_strjoin(str, function[0].t_function_pointer(output, &i));
		else if (output[i] == function[1].quote)
			str = ft_strjoin(str, function[1].t_function_pointer(output, &i));
		else
			str = ft_strjoin(str, function[2].t_function_pointer(output, &i));
		i++;
	}
	return (str);
}

void	tokenizer(char *output)
{
	t_check	check;
	char	*test;

	init_check(&check);
	output = remove_white_spaces(output, &check);
	test = state_macchine(output);
	printf("output = %s\n", test);
	free(test);
}
