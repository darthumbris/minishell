/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 11:59:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/03 12:14:44 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char *str, char **envp)
{
	int		i;
	int		len;
	char	*joined;

	if (envp)
	{
		i = 2;
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
	char	**dup;
	int		i;

	i = 0;
	dup = ft_calloc(1024, sizeof(char *));
	if (!dup)
		return (NULL);
	while (envp[i])
	{
		dup[i + 2] = ft_strdup(envp[i]);
		i++;
	}
	dup[0] = ft_strdup("0");
	dup[1] = ft_strdup("00");
	dup[1][0] = 0;
	dup[1][1] = 0;
	return (dup);
}
