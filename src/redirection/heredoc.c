/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:11:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/02 13:13:47 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function should handle the
 * << redirect and make an heredoc
 * that properly closes with the
 * input name (EOF or another word etc.)
 * than should write everything correctly
 * to the fd_outpout.
 */
void	heredoc_function(void)
{
	printf("entered heredoc redirection << function\n");
}
