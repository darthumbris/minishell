/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_evaluator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 10:23:08 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/04 11:38:54 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <limits.h>

/*
 * This function evalutes the redirection token.
 * It will check for correct amount of redirection chars.
 * it will also check if there is a token after this,
 * it also checks for bad file descriptors.
 */
void	evaluate_redirection(t_token *lst)
{
	int	i;
	int	len;

	if (!lst->next)
		printf("minishell: syntax error near unexpected token `newline'\n");
	i = 0;
	while (ft_isdigit(lst->token_value[i]))
		i++;
	len = i;
	while (lst->token_value[i] == lst->token_value[len])
		i++;
	if (i - len > 2)
		printf("minishell: syntax error near unexpected token `%c'\n", \
			lst->token_name[0]);
	else if (ft_isdigit(lst->token_value[0]) && ft_atoi(lst->token_value) > 255)
	{
		if (ft_atoi(lst->token_value) > INT_MAX)
			printf("minishell: file descriptor out of range: \
			Bad file descriptor\n");
		else
			printf("minishell: %d Bad file descriptor\n", \
			ft_atoi(lst->token_value));
	}
	else if (*lst->next->token_value == '>' || *lst->next->token_value == '<')
		printf("minishell: syntax error near unexpected token `%c'\n", \
			lst->next->token_value[0]);
}

/*
 * This function will evaluate the pipe token
 * and will check if there was a command before the 
 * pipe and if the amount of pipes in the pipe token 
 * is not more than 1.
 */
void	evaluate_pipe(t_token *current, t_token *prev)
{
	if (ft_strlen(current->token_value) > 1)
		printf("minishell: syntax error near unexpected token `|'\n");
	else if (prev->token_name[0] != 'W' && prev->token_name[0] != 'F')
		printf("minishell: syntax error near unexpected token `|'\n");
	else if (current->next && current->next->token_name[0] == '|')
		printf("minishell: syntax error near unexpected token `|'\n");
}

/*
 * The evaluator function will check
 * all the tokens if they don't have syntax errors.
 * In the parser the commands need to be validated.
 */
void	evaluator(t_token *lst)
{
	t_token	*current;
	t_token	*prev;

	current = lst;
	while (current)
	{
		if (current->token_name[0] == '|')
			evaluate_pipe(current, prev);
		else if (current->token_name[0] == '>' || current->token_name[0] == '<')
			evaluate_redirection(current);
		prev = current;
		current = current->next;
	}
}
