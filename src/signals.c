/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 11:07:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/02/28 15:41:19 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function handles the ctrl-c for now
 * it will make a new line and clear the input.
 * need to figure out how to handle the ctr-\ thing
 * also do something different when in a functin/command
 * and with just normal input should do the replace stuff
 */
void	signal_handle_function(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

void	signal_handle_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signals(void)
{
	signal(SIGINT, signal_handle_child);
	signal(SIGQUIT, signal_handle_child);
}

void	disable_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
