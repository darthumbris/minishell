/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_functions2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:14:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/28 13:09:17 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * exit function will exit the minishell
 * with the exit value given as argument (or 255 if non numeric argument given)
 * if there are too many arguments (more than 1) it will exit with 1.
 * still need to free the envp and input.
 */
void	exit_function(char **input, char **envp)
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

/*
 * echo command should check for the -n option
 * and than just print all the arguments
 * (-nnnnnn is also valid option or -nn -nn too)
 * echo will print a space between each argument:
 * echo asdf      fasdf (will print asdf fasdf)
 */
void	echo_function(char **input, char **envp)
{
	if (input && *input == ' ' && envp)
		printf("entered echo function\n");
}
