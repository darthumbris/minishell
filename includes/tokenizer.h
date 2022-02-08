/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 15:03:21 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/08 10:46:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdbool.h>
# include "libft.h"

typedef struct s_token
{
	char			*token_name;
	char			*token_value;
	struct s_token	*next;
}			t_token;

//----------Lexur functions-----------
t_token	*lexer(char *input);
int		move_through_quotes(char *input, int i);
int		move_through_spaces(char *input, int i);
void	redirect_function(char *input, int *i, int *word_start, t_token *lst);
//------token-functions
int		add_redirection_token(char *input, t_token *token_lst, int i);
void	add_word_token(char *input, t_token *token_lst, int start, int end);
void	add_new_token(t_token **lst, t_token *new);
t_token	*new_token(char *token_name, char *token_value);
void	free_token_lst(t_token **lst);
t_token	*get_last_token(t_token *lst);
//-----evaluator functions---------------
bool	evaluator(t_token *lst);
int		is_valid_fd_redirect(char *input, int start, int end);
//----------expansion functions-----------
t_token	*quote_expansion(t_token *lst);
char	*check_for_expans(char *input);
int		len_until_char(char *str, int i, char c);
int		len_until_quote(char *str, int i);
void	check_for_env_expansion(char **str, char **envp);
#endif