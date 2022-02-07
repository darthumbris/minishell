/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 11:59:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/02 15:32:57 by shoogenb      ########   odam.nl         */
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

void	change_pwd_in_envp(char **envp)
{
	char	*pwd_change;
	char	*old_pwd_change;
	char	*new_path;

	new_path = getcwd(NULL, -1);
	pwd_change = ft_strjoin("PWD=", new_path);
	old_pwd_change = ft_strjoin("OLDPWD=", ft_getenv("PWD", envp));
	export_function(old_pwd_change, envp);
	export_function(pwd_change, envp);
	free(pwd_change);
	free(new_path);
	free(old_pwd_change);
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

/*
 * This function returns the expanded string with
 * the env variable that is expanded to its value.
 * (needs to be properly freed afterwards).
 */
char	*normal_env_variable(char *input, char **envp, int len)
{
	char	*env_str;
	char	*env_expand;
	char	*remain;

	env_str = ft_substr(input, 0, \
				(ft_strchr(input, ' ') - input));
	if (!ft_getenv(env_str, envp))
	{
		env_expand = ft_substr(input, ft_strlen(env_str) + 1, len);
		free(env_str);
		return (env_expand);
	}
	remain = ft_substr(input, ft_strlen(env_str), len);
	env_expand = ft_strjoin(ft_getenv(env_str, envp), remain);
	free(remain);
	free(env_str);
	return (env_expand);
}

/*
 * This function will expand the $ stuff 
 * $? $0 and $PWD (and other env variables)
 * are covered with this function.
 * the returned string should be freed properly.!
 * !!!!return value still needs to be done. !!!!!
 */
char	*expand_env_variable(char *input, char **envp)
{
	int		len;
	char	*env_expand;
	char	*remain;

	if (input && *input)
	{
		len = ft_strlen(input);
		if (*input == '0')
		{
			remain = ft_substr(input, 1, len);
			env_expand = ft_strjoin("minishell", remain);
		}
		else if (*input == '?')
		{
			remain = ft_substr(input, 1, len);
			env_expand = ft_strjoin(ft_itoa(0), remain);
		}
		else
			return (normal_env_variable(input, envp, len));
		free(remain);
		return (env_expand);
	}
	return (NULL);
}
