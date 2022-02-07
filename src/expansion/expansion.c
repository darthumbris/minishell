/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 10:31:50 by abba          #+#    #+#                 */
/*   Updated: 2022/02/07 12:37:17 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "quotes.h"

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

//this function return the len of list so we can get the exact size to malloc
int lstsize(t_token *lst)
{
    int len;

    len = 0;
    while(lst)
    {
        len++;
        lst = lst->next;
    }
    return (len);
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

t_token *expansion(t_token *lst)
{
    char	**value;
    int		len;
    t_token	*tmp;
	
	lst = lst->next;
    len = lstsize(lst);
    value = ft_calloc(len + 1, sizeof(char *));
    if (!value)
        return (0);
    len = 0;
	while(lst)
	{
        tmp = lst->next;
        value[len] = check(lst->token_value);
        len++;
        free(lst);
		lst = tmp;
	}
    value[len] = NULL;
	len = 0;
	while (value[len])
	{
		free(value[len]);
		len++;
	}
	free(value);
    return (lst);
}
