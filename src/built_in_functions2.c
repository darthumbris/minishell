/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_functions2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:14:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/27 20:05:18 by abba          ########   odam.nl         */
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
			free(envp); // this is not a proper free!!! just a temp thing.
			exit(255);
		}
		i++;
	}
	printf("exit\n");
	system("leaks minishell");
	free(envp); // this is not a proper free!!! just a temp thing.
	exit(ft_atoi(input));
}

void	echo_function(char *input, char **envp)
{
	char	**echo_input;

	(void)envp;
	echo_input = ft_split(input, ' ');
	while (*echo_input)
	{
		printf("test[%s]\n", *echo_input);
		echo_input++;
	}
}
