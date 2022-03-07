/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/05 13:12:59 by abba          #+#    #+#                 */
/*   Updated: 2022/03/07 10:39:35 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	swap(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

static bool	is_sorted(char **envp, int i)
{
	while (envp[i + 1])
	{
		if (ft_strcmp(envp[i], envp[i + 1]) > 0)
			return (false);
		i++;
	}
	return (true);
}

static void	call(char **envp, int i)
{
	while (envp[i + 1])
	{
		if (ft_strcmp(envp[i], envp[i + 1]) > 0)
			swap(&envp[i], &envp[i + 1]);
		i++;
	}
	print_export(envp);
}

void	print_export(char **envp)
{
	int		i;
	char	*var;

	i = 4;
	if (is_sorted(envp, i))
	{
		while (envp[i])
		{
			if (!has_equals(envp[i]))
				printf("declare -x %s\n", envp[i]);
			else if (ft_isalpha(envp[i][0]) || envp[i][0] == '_')
			{
				var = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') \
					- envp[i] + 1);
				if (ft_strcmp(var, "_="))
					printf("declare -x %s\"%s\"\n", var, \
						ft_strchr(envp[i], '=') + 1);
				free(var);
			}
			i++;
		}
		return (free_cmd_args(envp));
	}
	else
		call(envp, i);
}
