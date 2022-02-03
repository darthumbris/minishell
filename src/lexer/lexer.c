/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 12:04:32 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/03 16:41:54 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "stdio.h"

void	add_file_token(char *input, t_token *token_lst, int start, int end)
{
	if (end > start)
		add_new_token(&token_lst, new_token
			("F", ft_substr(input, start, end - start)));
}

void	add_word_token(char *input, t_token *token_lst, int start, int end)
{
	if (end > start)
		add_new_token(&token_lst, new_token
			("W", ft_substr(input, start, end - start)));
}

int	add_redirection_token(char *input, t_token *token_lst, int i)
{
	int	start;

	start = i;
	while (input[i] == input[start])
		i++;
	if (i - start > 2)
		printf("error thing here\n");
	else if (input[start] == '>')
		add_new_token(&token_lst, new_token
			(">", ft_substr(input, start, i - start)));
	else if (input[start] == '<')
		add_new_token(&token_lst, new_token
			("<", ft_substr(input, start, i - start)));
	start = move_through_spaces(input, i);
	i = start;
	while (ft_isalnum(input[i]))
		i++;
	add_file_token(input, token_lst, start, i);
	i = move_through_spaces(input, i);
	return (i);
}

int	add_pipe_token(char *input, t_token *token_lst, int i)
{
	int	start;

	start = i;
	while (input[i] == input[start])
		i++;
	if (i - start > 1)
		printf("error thing here\n");
	else
		add_new_token(&token_lst, new_token
			("|", ft_substr(input, start, i - 1 - start)));
	i = move_through_spaces(input, i);
	return (i);
}

/*
 * This function will split
 * up the input string in
 * either words, redirects pipe
 * or filename token.
 * and create a linked list with that.
 */
t_token	*lexer(char *input)
{
	int		i;
	int		word_start;
	t_token	*lst;

	i = 0;
	word_start = 0;
	lst = new_token("B", "");
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = move_through_quotes(input, i);
		if (input[i] == ' ') //&& ft_isalnum(input[i + 1]) ?
		{
			add_word_token(input, lst, word_start, i);
			i = move_through_spaces(input, i) - 1;
			word_start = i + 1;
		}
		else if (input[i] == '>' || input[i] == '<')
		{
			//need to do a check here if word created below is all digits. 
			//than part of redirect.
			if (is_valid_fd_redirect(input, word_start, i))
				printf("valid fd redirect!!\n");
			add_word_token(input, lst, word_start, i);
			i = add_redirection_token(input, lst, i) - 1;
			word_start = i + 1;
		}
		else if (input[i] == '|')
		{
			add_word_token(input, lst, word_start, i);
			i = add_pipe_token(input, lst, i) - 1;
			word_start = i + 1;
		}
		i++;
	}
	add_word_token(input, lst, word_start, i);
	return (lst);
}
