/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_function.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:53:45 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/03 17:06:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	change_pwd_in_envp(char **envp)
{
	char		*pwd_change;
	char		*old_pwd_change;
	char		*new_path;

	new_path = getcwd(NULL, -1);
	pwd_change = ft_strjoin("PWD=", new_path);
	old_pwd_change = ft_strjoin("OLDPWD=", ft_getenv("PWD", envp));
	export_simple(old_pwd_change, envp);
	export_simple(pwd_change, envp);
	free(new_path);
	free(pwd_change);
	free(old_pwd_change);
	set_return_value(envp, 0);
}

static void	cd_tilde(t_command *cmd, char **envp)
{
	char	*relative;
	char	*input;

	input = cmd->cmds[1];
	if (input[1] == '/' || input[1] == '\0' || input[1] == ' ')
	{
		if (!ft_getenv("HOME", envp))
			return (ft_putendl_fd("minishell: cd: HOME not set", 2));
		if (input[1] == ' ')
		{
			free(cmd->cmds[1]);
			cmd->cmds[1] = ft_strdup(ft_getenv("HOME", envp));
			return (cd_function(cmd, envp));
		}
		relative = ft_strjoin(ft_getenv("HOME", envp), input + 1);
	}
	else
		relative = ft_strjoin("/Users/", input + 1);
	input = relative;
	free(relative);
	cd_function(cmd, envp);
}

static void	cd_dash(t_command *cmd, char **envp)
{
	char	*input;

	input = cmd->cmds[1];
	if (!input)
		ft_putendl_fd("cd Error", 2);
	if (ft_getenv("OLDPWD", envp))
	{
		ft_putendl_fd(ft_getenv("OLDPWD", envp), 1);
		free(cmd->cmds[1]);
		cmd->cmds[1] = ft_strdup(ft_getenv("OLDPWD", envp));
		cd_function(cmd, envp);
	}
	else
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
}

static void	cd_error(t_command *cmd, char **envp)
{
	ft_putstr_fd("minishell: ", cmd->fd_error);
	ft_putstr_fd(cmd->cmds[1], cmd->fd_error);
	ft_putendl_fd(": No such file or directory", cmd->fd_error);
	set_return_value(envp, 1);
}

/*
 * The cd function will check the input 
 * and then try to change the directory with
 * chdir.
 * it should also handle cd - (go back to previous dir)
 * and also cd ~ or cd ~/Documents (where ~ is home dir)
 * or cd ~username (than it should move to homedir of other user)
 */
void	cd_function(t_command *cmd, char **envp)
{
	if (!cmd->cmds[1])
	{
		if (!ft_getenv("HOME", envp))
			return (ft_putendl_fd("minishell: cd: HOME not set", 2));
		if (chdir(ft_getenv("HOME", envp)) == -1)
			perror("");
		else
			change_pwd_in_envp(envp);
	}
	else if (cmd && cmd->cmds && cmd->cmds[1][0] != '\0')
	{
		if (*cmd->cmds[1] == '-' && \
			(cmd->cmds[1][1] == ' ' || cmd->cmds[1][1] == '\0'))
			cd_dash(cmd, envp);
		else if (*cmd->cmds[1] == '~')
			cd_tilde(cmd, envp);
		else if (chdir(cmd->cmds[1]) == -1)
			cd_error(cmd, envp);
		else
			change_pwd_in_envp(envp);
	}
}
