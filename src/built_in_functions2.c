/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_functions2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:14:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/27 16:24:53 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_function(char *input, char **envp)
{
	int	i;

	i = 0;
	input = ft_whitespaces(input);
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
		{
			printf("exit\nminishell>: exit: %s: numeric argument required\n", \
				input);
			system("leaks minishell");
			free(envp);
			exit(255);
		}
		i++;
	}
	printf("exit\n");
	system("leaks minishell");
	free(envp);
	exit(ft_atoi(input));
}

void	echo_function(char *input, char **envp)
{
	if (input && *input == ' ' && envp)
		printf("entered echo function\n");
}
