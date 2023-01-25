/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/01/24 20:32:37 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	sig = 1;
	exit(0);
	write(1, "\nminishell $> ", 14);
}

void	sigauit_handler(int sig)
{
	(void)sig;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigauit_handler);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_main_args	main_args;

	main_args.ac = ac;
	main_args.av = av;
	main_args.env = env;
	init_signals();
	while (1)
	{
		line = readline(("minishell $> "));
		if (line == NULL)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		if (*line != 0)
			add_history(line);
		handle_line(line, &main_args);
		rl_redisplay();
		free(line);
	}
	/*
	while (1)
	{

		write(1, "minishell >", 11);
		line = get_next_line(0);
		if (line != 0)
		{
			if (line[0] != '\n')
			{
				handle_line(line, &main_args);
				write(1, "\n", 1);
			}
			free(line);
		}
		else
		{
			write(1, "exit\n", 5);
			exit (0);
		}
	}*/
	return (0);
}
