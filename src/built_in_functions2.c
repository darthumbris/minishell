/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_functions2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:14:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/27 12:15:51 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_function(char *input, char **envp)
{
	if (input && !ft_isalpha(*input) && !ft_isdigit(*input) && envp)
	{
		printf("exit\n");
		system("leaks minishell");
		exit(0);
	}
	else
	{
		ft_putstr_fd("exit", 2);
		ft_putstr_fd(input, 2);
		ft_putendl_fd(": command not found", 2);
	}
}

void	echo_function(char *input, char **envp)
{
	if (input && *input == ' ' && envp)
		printf("entered echo function\n");
}
