/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_lst.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 10:05:22 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/03 11:10:28 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "tokenizer.h"

int	check_for_redirection(char *word)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (word[i])
	{
		if ((word[i] == '>' || word[i] == '<') && !quotes)
			return (1);
		if (word[i] == '\"' || word[i] == '\'')
		{
			if (quotes == 0 && word[i] == '\"')
				quotes = 1;
			else if (quotes == 1 && word[i] == '\"')
				quotes = 0;
			else if (quotes == 0 && word[i] == '\'')
				quotes = 2;
			else if (quotes == 2 && word[i] == '\'')
				quotes = 0;
		}
		i++;
	}
	return (0);
}

int	check_for_pipe(char *word)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (word[i])
	{
		if (word[i] == '|' && !quotes)
			return (1);
		if (word[i] == '\"' || word[i] == '\'')
		{
			if (quotes == 0 && word[i] == '\"')
				quotes = 1;
			else if (quotes == 1 && word[i] == '\"')
				quotes = 0;
			else if (quotes == 0 && word[i] == '\'')
				quotes = 2;
			else if (quotes == 2 && word[i] == '\'')
				quotes = 0;
		}
		i++;
	}
	return (0);
}

t_token	*tokenizer_lst(char **tokens)
{
	int		i;
	t_token	*token_lst;

	i = 0;
	while (tokens[i])
	{
		if (check_for_redirection(tokens[i]))
			add_redirect_token(tokens[i], token_lst);
		else if (check_for_pipe(tokens[i]))
			add_pipe_token(tokens[i], token_lst);
		else
			add_word_token(tokens[i], token_lst);
		i++;
	}
}
