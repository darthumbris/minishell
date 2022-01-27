/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 11:59:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/27 13:19:57 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str, char **envp)
{
	int	i;
	int	len;

	if (envp)
	{
		i = 0;
		len = ft_strlen(str);
		while (envp[i])
		{
			if (ft_strncmp(str, envp[i], len) == 0)
				break ;
			i++;
		}
		if (envp[i])
			return (envp[i] + len + 1);
	}
	return (NULL);
}

void	change_pwd_in_envp(char **envp)
{
	char	*pwd_change;
	char	*old_pwd_change;
	char	*new_path;

	new_path = getcwd(NULL, -1);
	pwd_change = ft_strjoin(" PWD=", new_path);
	old_pwd_change = ft_strjoin(" OLDPWD=", ft_getenv("PWD", envp));
	export_function(old_pwd_change, envp);
	export_function(pwd_change, envp);
	printf("in pwd change send this to export function: %s\n", pwd_change);
	printf("in pwd change send this to export function: %s\n", old_pwd_change);
	free(pwd_change);
	free(new_path);
	free(old_pwd_change);
}
