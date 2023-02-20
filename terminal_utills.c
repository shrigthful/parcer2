/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utills.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/02/20 20:37:22 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(void)
{
	struct termios	term;
	struct termios	oldterm;
	char			*line;

	tcgetattr(0, &term);
	oldterm = term;
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	line = readline(("minishell $> "));
	tcsetattr(0, TCSANOW, &oldterm);
	return (line);
}

void	sigint_handler(int sig)
{
	sig = 1;
	write(1, "\n", 1);
	if (g_vars.line_handled == 0)
	{
		//rl_replace_line("", 1);
		//rl_on_new_line();
		rl_redisplay();
	}
	g_vars.last_exit_sat = 1;
}

void	sigauit_handler(int sig)
{
	printf("Quit: 3\n");
	(void)sig;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigauit_handler);
}
