/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:01:40 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/04 11:31:06 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
 * This function will iterate until it
 * gets to the corresponding closing quote
 * it will then return the position after
 * the closing quote.
 */
int	move_through_quotes(char *input, int i)
{
	int	start;

	start = i;
	i++;
	while (input[i] && input[i] != input[start])
		i++;
	return (i);
}

/*
 * This function will iterate through all 
 * spaces and will return the position
 * after the last space.
 */
int	move_through_spaces(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}

/*
 * This function will check if the 
 * characters before the redirection
 * are only numbers and thus can represent
 * a file descriptor.
 */
int	is_valid_fd_redirect(char *input, int start, int end)
{
	if (end == start)
		return (0);
	while (input[start] && start < end)
	{
		if (!ft_isdigit(input[start]))
			return (0);
		start++;
	}
	return (1);
}

/*
 * This function either makes a redirection token with added filedescriptor
 * or will add a word token (for example asd> will make asd as a word token)
 * and then an redirection token.
 * in the add_red_token function it will also add the file token if it can.
 */
void	redirect_function(char *input, int *i, int *word_start, t_token *lst)
{
	if (is_valid_fd_redirect(input, *word_start, *i))
		*i = add_redirection_token(input, lst, *word_start) - 1;
	else
	{
		add_word_token(input, lst, *word_start, *i);
		*i = add_redirection_token(input, lst, *i) - 1;
	}
	*word_start = *i + 1;
}
