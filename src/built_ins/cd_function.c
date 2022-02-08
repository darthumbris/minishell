/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_function.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:53:45 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/08 13:35:32 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_pwd_in_envp(char **envp)
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

static void	cd_tilde(char *input, char **envp)
{
	char	*relative;

	if (input[1] == '/' || input[1] == '\0' || input[1] == ' ')
	{
		if (!ft_getenv("HOME", envp))
			return (ft_putendl_fd("minishell: cd: HOME not set", 2));
		if (input[1] == ' ')
			return (cd_function(ft_getenv("HOME", envp), envp));
		relative = ft_strjoin(ft_getenv("HOME", envp), input + 1);
	}
	else
		relative = ft_strjoin("/Users/", input + 1);
	input = relative;
	free(relative);
	cd_function(input, envp);
}

static void	cd_dash(char *input, char **envp)
{
	if (!input)
		ft_putendl_fd("cd Error", 2);
	if (ft_getenv("OLDPWD", envp))
	{
		ft_putendl_fd(ft_getenv("OLDPWD", envp), 1);
		cd_function(ft_getenv("OLDPWD", envp), envp);
	}
	else
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
}

/*
 * The cd function will check the input 
 * and then try to change the directory with
 * chdir.
 * it should also handle cd - (go back to previous dir)
 * and also cd ~ or cd ~/Documents (where ~ is home dir)
 * or cd ~username (than it should move to homedir of other user)
 */
void	cd_function(char *input, char **envp)
{
	input = ft_whitespaces(input);
	if (!*input)
	{
		if (chdir(ft_getenv("HOME", envp)) == -1)
			perror("");
		else
			change_pwd_in_envp(envp);
	}
	else
	{
		if (*input == '-' && (input[1] == ' ' || input[1] == '\0'))
			cd_dash(input, envp);
		else if (*input == '~')
			cd_tilde(input, envp);
		else if (chdir(input) == -1)
			perror("");
		else
			change_pwd_in_envp(envp);
	}
}
