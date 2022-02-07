/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 10:53:42 by abba          #+#    #+#                 */
/*   Updated: 2022/02/07 15:07:37 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H
typedef struct s_quote
{
	char	quote;
	char	*(*t_function_pointer)(char *input, int *i);
}			t_quote;

#endif