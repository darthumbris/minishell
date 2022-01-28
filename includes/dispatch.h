/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatch.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:14:52 by abba          #+#    #+#                 */
/*   Updated: 2022/01/28 12:37:24 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCH_H
# define DISPATCH_H

typedef struct s_cmd
{
	char	*comand;
	void	(*t_function_pointer)(char *input, char **envp);
}			t_cmd;

#endif