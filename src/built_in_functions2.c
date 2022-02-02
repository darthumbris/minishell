/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_functions2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:14:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/02 12:10:18 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * exit function will exit the minishell
 * with the exit value given as argument (or 255 if non numeric argument given)
 * if there are too many arguments (more than 1) it will exit with 1.
 * still need to free the envp and input.
 */
void	exit_function(char *input, char **envp)
{
	int	i;

	i = 0;
	input = ft_whitespaces(input);
	while (input[i] && envp)
	{
		if (!ft_isdigit(input[i]))
		{
			printf("exit\nminishell>: exit: %s: numeric argument required\n", \
				input);
			if (ft_atoi(ft_getenv("SHLVL=", envp)) == 1)
				exit(255);
			change_shl_lvl(envp, -1);
		}
		i++;
	}
	printf("exit\n");
	if (ft_atoi(ft_getenv("SHLVL=", envp)) == 1)
		exit(ft_atoi(input));
	change_shl_lvl(envp, -1);
}

/*
 * echo command should check for the -n option
 * and than just print all the arguments
 * (-nnnnnn is also valid option or -nn -nn too)
 * echo will print a space between each argument:
 * echo asdf      fasdf (will print asdf fasdf)
 */
void	echo_function(char *input, char **envp)
{
	int	len;
	int	i;

	input = ft_whitespaces(input);
	len = ft_strlen(input);
	i = 1;
	if (*input == '-' && len > 1 && input[1] == 'n')
	{
		while (input[i] == 'n' && input[i])
			i++;
		if (input[i] != ' ')
			return (ft_putendl_fd(input, 1));
		else
			input = ft_whitespaces(input + i);
		if (input[0] == '-' && input[1] == 'n')
			echo_function(input, envp);
		else
			ft_putstr_fd(input, 1);
	}
	else
		ft_putendl_fd(input, 1);
}
