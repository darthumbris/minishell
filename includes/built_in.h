/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 10:24:33 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/07 09:43:29 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "command.h"
# include <stdio.h>
# include "libft.h"

//---------Shell  Built-in-functions--------------
void		cd_function(t_command *cmd, char **envp);
void		pwd_function(t_command *cmd, char **envp);
void		export_function(t_command *cmd, char **envp);
void		unset_function(t_command *cmd, char **envp);
void		env_function(t_command *cmd, char **envp);
void		exit_function(t_command *cmd, char **envp);
void		echo_function(t_command *cmd, char **envp);
//---------Shell  Built-in-functions Utils--------------
bool		is_valid_var_name(char *input);
void		identifier_msg(char *input, char *cmd, int fd);
bool		is_valid_exit(t_command *cmd);
bool		is_built_in(t_command *cmd);
bool		has_equals(char *input);
void		print_export(char **envp);

//----------envp functions------------------------
void		export_simple(char *input, char **envp);
void		change_shl_lvl(char **envp, int change);
char		**envp_duplicate(char **envp);
void		set_return_value(char **envp, int nbr);
char		*ft_getenv(char *str, char **envp);
#endif