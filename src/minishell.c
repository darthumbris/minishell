/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:13:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/24 15:17:25 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

/*
 * !!!need to properly check the shlvl at
 * the start of program. Or increase it by 1
 * at the beginning. not sure yet what is 
 * correct.
 * Probably have a global struct
 * with a shlvl and return value
 * and maybe some other stuff
 * that bash stores itself and in env
 * or might be able to store it differently.
 */
int	main(int argc, char **argv, char **envp)
{
	static char		*input;
	char			**envp_dup;

	rl_catch_signals = 0;
	(void)argc;
	(void)argv;
	set_signals();
	envp_dup = envp_duplicate(envp);
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
