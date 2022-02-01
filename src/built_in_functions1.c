/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_functions1.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:12:01 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/01 14:53:41 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * the pwd function just needs to handle the pwd
 * it doesn't need any arguments. (and won't complain if there are any in bash)
 */
void	pwd_function(char *input, char **envp)
{
	char	*pwd_str;

	if (input && envp)
	{
		pwd_str = getcwd(NULL, -1);
		if (!pwd_str)
			printf("%s\n", ft_getenv("PWD=", envp));
		else
		{
			printf("%s\n", pwd_str);
			free(pwd_str);
		}		
	}
}

/*
 * This function handles the export function
 * export can handle stuff like: export test=water like=bake
 * and will do both arguments.
 */
void	export_function(char *input, char **envp)
{
	int		i;
	char	*export_var;

	export_var = ft_substr(input, 0, ft_strchr(input, '=') - input);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], export_var, ft_strlen(export_var)) == 0)
		{
			free(envp[i]);
			envp[i] = NULL;
		}
		i++;
	}
	i = 0;
	while (envp[i])
		i++;
	envp[i] = ft_strdup(input);
	free(export_var);
}

/*
 * The unset function the same as the export function
 * should accept multiple arguments to unset.
 */
void	unset_function(char *input, char **envp)
{
	int		i;

	i = 0;
	input = ft_whitespaces(input);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], input, ft_strlen(input)) == 0)
		{
			free(envp[i]);
			while (envp[i + 1])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
		}
		i++;
	}
}

/*
 * The env doesn't need to accept any options or arguments.
 * it will just print the env no matter what
 * (in bash the argument needs to be an env variable and it will
 * print only the value of that variable)
 */
void	env_function(char *input, char **envp)
{
	int	i;

	i = 0;
	if (input && envp)
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
}
