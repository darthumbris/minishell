/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_functions1.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:12:01 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/27 12:14:07 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * The cd function will check the input 
 * and then try to change the directory with
 * chdir.
 */
void	cd_function(char *input, char **envp)
{
	(void)envp;
	input = ft_whitespaces(input);
	if (!*input)
	{
		if (chdir(ft_getenv("HOME", envp)) == -1)
			perror("testing");
		else
			change_pwd_in_envp(ft_getenv("HOME", envp), envp);
	}
	else
	{
		if (chdir(input) == -1)
			perror("");
		else
			change_pwd_in_envp(input, envp);
	}
}

void	pwd_function(char *input, char **envp)
{
	char	*pwd_str;

	if (input && !ft_isalpha(*input) && !ft_isdigit(*input) && envp)
	{
		pwd_str = getcwd(NULL, -1);
		if (!pwd_str)
			printf("%s\n", ft_getenv("PWD", envp));
		else
		{
			printf("%s\n", pwd_str);
			free(pwd_str);
		}		
	}
}

void	export_function(char *input, char **envp)
{
	if (input && *input == ' ' && envp)
		printf("entered export function\n");
}

void	unset_function(char *input, char **envp)
{
	if (input && *input == ' ' && envp)
		printf("entered unset function\n");
}

void	env_function(char *input, char **envp)
{
	int	i;

	i = 0;
	if (input && !ft_isalpha(*input) && !ft_isdigit(*input) && envp)
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
}
