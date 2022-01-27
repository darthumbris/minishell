/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_duplicate.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 11:51:24 by abba          #+#    #+#                 */
/*   Updated: 2022/01/27 12:12:27 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	return (i);
}

char	**envp_duplicate(char **envp)
{
	int		len;
	char	**tmp;
	int		i;

	i = 0;
	len = envp_len(envp);
	tmp = malloc((len + 1) * sizeof(char *));
	while (i < len)
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}
