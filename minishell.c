/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/01/22 19:54:03 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	exit(1);
	write(1, "\nminishell >", 12);
	sig = 1;
}

void	sigauit_handler(int sig)
{
	sig = 1;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigauit_handler);
}

int	main(void)
{
	char	*line;

	init_signals();
	while (1)
	{
		write(1, "minishell >", 11);
		line = get_next_line(0);
		if (line != 0)
		{
			if (line[0] != '\n')
			{
				write(1, line, ft_strlen(line));
				handle_line(line);
				write(1, "\n", 1);
			}
			free(line);
		}
		else
		{
			write(1, "exit\n", 5);
			exit (0);
		}
	}
	return (0);
}
