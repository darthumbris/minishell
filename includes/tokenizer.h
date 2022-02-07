/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 15:03:21 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/07 15:12:27 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdbool.h>
# include "libft.h"

typedef struct s_check
{
	int		count_s;
	int		count_d;
	int		len;
	int		position;
	bool	single_quote;
	bool	double_quotes;
}		t_check;

//enum might be nicer to use?
// enum e_token_names
// {
// 	TOKEN_WORD,
// 	TOKEN_FILENAME,
// 	TOKEN_PIPE = '|',
// 	TOKEN_REDIRECT_OUTPUT = '>',
// 	TOKEN_REDIRECT_INPUT = '<'
// };

typedef struct s_token
{
	char			*token_name;
	char			*token_value;
	struct s_token	*next;
}			t_token;

//------tokenizer functions--------(might not be needed anymore)
char	*remove_white_spaces(char *str, t_check *check);
void	fill_str(char	*str, int *j, int i);
void	double_quotes(t_check *check);
void	single_quote(t_check *check);
void	init_check(t_check *check);

//----------Lexur functions-----------
t_token	*lexer(char *input);
int		move_through_quotes(char *input, int i);
int		move_through_spaces(char *input, int i);
void	add_new_token(t_token **lst, t_token *new);
t_token	*new_token(char *token_name, char *token_value);
int		is_valid_fd_redirect(char *input, int start, int end);
void	redirect_function(char *input, int *i, int *word_start, t_token *lst);
int		add_redirection_token(char *input, t_token *token_lst, int i);
void	add_word_token(char *input, t_token *token_lst, int start, int end);
void	free_token_lst(t_token **lst);
bool	evaluator(t_token *lst);

//----------expansion functions-----------
t_token *expansion(t_token *lst);
char	*check(char *input);
int		ft_count(char *str, int i, char c);
int		ft_count1(char *str, int i);

#endif