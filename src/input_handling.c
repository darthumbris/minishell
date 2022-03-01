/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 14:38:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/01 15:37:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This functions uses readline to get input
 * in the shell and will add it to the history
 * when needed (so no empty stuff).
 * It will also close when EOF (ctrl-D)
 * this might need some work for some cases.
 * might need a check for echo cd pwd etc.
 * need to see how to do this properly.
 * also need to check when history should be
 * and should not be added.
 */
char	*get_input(char *input)
{
	if (input)
	{
		free(input);
		input = NULL;
	}
	input = readline("minishell> ");
	if (input && *input)
		add_history(input);
	return (input);
}
