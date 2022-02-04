/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shlvl.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 12:04:38 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/04 13:27:18 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function might be unnecesary if the cmd_exec etc. works correctly.
void	change_shl_lvl(char **envp, int change)
{
	char	*shlvl;
	int		shlvl_current;
	char	*new_shlvl;

	shlvl_current = ft_atoi(ft_getenv("SHLVL", envp));
	new_shlvl = ft_itoa(shlvl_current + change);
	shlvl = ft_strjoin("SHLVL=", new_shlvl);
	free(new_shlvl);
	export_function(shlvl, envp);
	free(shlvl);
}
