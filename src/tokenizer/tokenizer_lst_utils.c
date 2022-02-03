/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_lst_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 11:27:29 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/03 11:57:34 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

t_token	*new_token(char *token_name, char *token_value)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->token_name = token_name;
	new->token_value = token_value;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **lst, t_token *new)
{
	
}

void	add_input_token(char *word, t_token *token_lst, int start, int end)
{
	
}

void	add_output_token(char *word, t_token *token_lst, int start, int end)
{
	
}

void	add_redirect_token(char *word, t_token *token_lst)
{
	int	i;
	int	digit;

	i = 0;
	while (word[i])
	{
		digit = i;
		while (ft_isdigit(word[i]))
			i++;
		if (word[i] == '<')
		{
			if (word[i + 1] == word[i] && ft_isalnum(word[i + 2]))
				add_input_token(word, token_lst, digit, i + 1);
			else if (ft_isalnum(word[i + 1]))
				add_input_token(word, token_lst, digit, i);
		}
		else if (word[i] == '>')
		{
			if (word[i + 1] == word[i] && ft_isalnum(word[i + 2]))
				add_output_token(word, token_lst, digit, i + 1);
			else if (ft_isalnum(word[i + 1]))
				add_output_token(word, token_lst, digit, i);
		}
		i++;
	}
}

void	add_pipe_token(char *word, t_token *token_lst)
{
	
}

void	add_word_token(char *word, t_token *token_lst)
{
	
}
