/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatch.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:14:52 by abba          #+#    #+#                 */
/*   Updated: 2022/01/27 10:56:44 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCH_H
# define DISPATCH_H

enum e_builtins
{
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_ECHO
};
typedef void(*t_functionPointer)(char *input, char **envp);

#endif