/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/03 15:08:55 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "signals.h"
#include "built_in.h"

static int	envp_dup_err(void)
{
	ft_putendl_fd("Error duplicating envp", 2);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	static char		*input;
	char			**envp_dup;

	rl_catch_signals = 0;
	(void)argc;
	(void)argv;
	envp_dup = envp_duplicate(envp);
	if (!envp_dup)
		return (envp_dup_err());
	change_shl_lvl(envp_dup, 1);
	while (1)
	{
		set_signals();
		input = get_input(input);
		if (input == NULL)
		{
			ft_putstr_fd("\x1b[1Aminishell> ", 1);
			ft_putendl_fd("exit", 2);
			exit(0);
		}
		if (input && *input)
			parse_input(input, envp_dup);
	}
	return (0);
}
