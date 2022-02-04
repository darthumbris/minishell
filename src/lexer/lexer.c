/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 12:04:32 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/04 11:27:14 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "stdio.h"

/*
 * This function will add a file token
 * this should be made after a redirection.
 */
void	add_file_token(char *input, t_token *token_lst, int start, int end)
{
	if (end > start)
		add_new_token(&token_lst, new_token
			("F", ft_substr(input, start, end - start)));
}

/*
 * This function will make a word token
 * this can be either a command or argument or option
 * or a string for echo for example.
 */
void	add_word_token(char *input, t_token *token_lst, int start, int end)
{
	if (end > start)
		add_new_token(&token_lst, new_token
			("W", ft_substr(input, start, end - start)));
}

/*
 * This function will check for digits first
 * and will then create a redirection token
 * If there are digits in the front it will
 * add those to the token_value
 * so the evaluator can check the filedescriptor.
 */
int	add_redirection_token(char *input, t_token *token_lst, int i)
{
	int	start;
	int	red_start;

	start = i;
	while (ft_isdigit(input[i]))
		i++;
	red_start = i;
	while (input[i] == input[red_start])
		i++;
	if (i - red_start > 2)
		printf("error thing here or maybe in evaluator\n");
	else if (input[red_start] == '>')
		add_new_token(&token_lst, new_token
			(">", ft_substr(input, start, i - start)));
	else if (input[red_start] == '<')
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

/*
 * This function will first create a word token
 * and than will create a pipe token.
 */
int	add_pipe_token(char *input, t_token *token_lst, int i, int *word_start)
{
	int	start;

	add_word_token(input, token_lst, *word_start, i);
	start = i;
	while (input[i] == input[start])
		i++;
	if (i - start > 1)
		printf("error thing here or maybe in evaluator\n");
	else
		add_new_token(&token_lst, new_token
			("|", ft_substr(input, start, i - 1 - start)));
	i = move_through_spaces(input, i);
	*word_start = i;
	return (i);
}

/*
 * This function will split
 * up the input string in
 * either words, redirects, pipe
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
	lst = new_token("B", ft_strdup("start of token lst"));
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = move_through_quotes(input, i);
		if (input[i] == ' ')
		{
			add_word_token(input, lst, word_start, i);
			i = move_through_spaces(input, i) - 1;
			word_start = i + 1;
		}
		else if (input[i] == '>' || input[i] == '<')
			redirect_function(input, &i, &word_start, lst);
		else if (input[i] == '|')
			i = add_pipe_token(input, lst, i, &word_start) - 1;
		i++;
	}
	add_word_token(input, lst, word_start, i);
	return (lst);
}
