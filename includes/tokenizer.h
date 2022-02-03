/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 15:03:21 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/03 16:20:25 by shoogenb      ########   odam.nl         */
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
enum e_token_names
{
	TOKEN_WORD,
	TOKEN_FILENAME,
	TOKEN_PIPE = '|',
	TOKEN_REDIRECT_OUTPUT = '>',
	TOKEN_REDIRECT_INPUT = '<'
};

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
#endif