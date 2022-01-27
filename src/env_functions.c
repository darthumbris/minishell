/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 11:59:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/27 12:11:01 by shoogenb      ########   odam.nl         */
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

void	change_pwd_in_envp(char *path, char **envp)
{
	if (path && envp)
		printf("changing PWD value\n");
}
