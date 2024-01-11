/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 10:32:42 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/02 10:41:18 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

//------------Signal Functions---------------
void		set_signals(void);
void		disable_signals(void);
void		signal_handle_function(int sig);
void		signal_heredoc(int sig);

#endif