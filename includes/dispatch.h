/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatch.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:14:52 by abba          #+#    #+#                 */
/*   Updated: 2022/02/08 11:48:39 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCH_H
# define DISPATCH_H

typedef struct s_cmd
{
	char	*comand;
	void	(*t_function_pointer)(t_command *cmd, char **envp);
}			t_cmd;

#endif