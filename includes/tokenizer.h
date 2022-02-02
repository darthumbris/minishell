/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 15:03:21 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/02 15:15:58 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdbool.h>

typedef struct s_check
{
	int		count_s;
	int		count_d;
	int		len;
	int		position;
	bool	single_quote;
	bool	double_quotes;
}		t_check;

char	*remove_white_spaces(char *str, t_check *check);
void	fill_str(char	*str, int *j, int i);
void	double_quotes(t_check *check);
void	single_quote(t_check *check);
void	init_check(t_check *check);
#endif