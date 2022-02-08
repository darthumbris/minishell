/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 11:59:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/08 13:34:42 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str, char **envp)
{
	int		i;
	int		len;
	char	*joined;

	if (envp)
	{
		i = 0;
		joined = ft_strjoin(str, "=");
		len = ft_strlen(joined);
		while (envp[i])
		{
			if (ft_strncmp(joined, envp[i], len) == 0)
				break ;
			i++;
		}
		free(joined);
		if (envp[i])
			return (envp[i] + len);
	}
	return (NULL);
}

char	**envp_duplicate(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(1024, sizeof(char *));
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (tmp);
}
