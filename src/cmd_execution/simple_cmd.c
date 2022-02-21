/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 15:41:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/21 13:30:19 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

bool	is_command_valid(t_command *cmd, char **envp, int i, char *input)
{
	char	**paths;
	char	*cmd_slash;
	char	*cmd_path;
	bool	ret;

	ret = false;
	if (input && (*input == '/' || (*input == '.' && input[1] == '/')))
		paths = path_input(input);
	else
		paths = get_path_str(envp);
	if (cmd->cmds)
		cmd_slash = ft_strjoin("/", cmd->cmds[0]);
	else
		cmd_slash = ft_strdup("");
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd_slash);
		if (!access(cmd_path, 0))
			ret = true;
		free(cmd_path);
		i++;
	}
	free(cmd_slash);
	return (ret);
}

void	check_valid_commands(t_token *lst, char **envp)
{
	t_token		*tmp;
	t_command	*cmd;

	tmp = lst;
	cmd = new_command(NULL);
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	while (tmp)
	{
		if (tmp->token_name[0] == 'W')
		{
			if (cmd->cmds)
				free_cmd_args(cmd->cmds);
			cmd = create_cmd_lst(&tmp, cmd, envp);
			if (!is_command_valid(cmd, envp, 0, cmd->cmds[0]) && \
				ft_strcmp(cmd->cmds[0], "exit") && \
				ft_strcmp(cmd->cmds[0], "unset") && \
				ft_strcmp(cmd->cmds[0], "export"))
				err_cmd_not_found(cmd->cmds[0]);
		}
		if (tmp)
			tmp = tmp->next;
	}
	if (cmd)
		free_cmds(cmd);
}

/*
 * For now the check input will handle the case with absolute path
 * and using envp. Wont work yet with relative path.
 * The get_cmd_args that it uses also doesn't yet handle quotes
 * and other difficult stuff.
 * things like echo $? or echo $USER and other commands.
 * will also give wrong error when doing absolute path stuff
 * for example /bin/wc will give command not found
 * instead of no such file or directory.
 */
void	execute_input(t_command *cmd, char **envp)
{
	char	**paths;
	char	*input;

	input = cmd->cmds[0];
	if (input && (*input == '/' || (*input == '.' && input[1] == '/')))
		paths = path_input(input);
	else
		paths = get_path_str(envp);
	command_exec(paths, cmd->cmds, envp);
	exit(127);
}
