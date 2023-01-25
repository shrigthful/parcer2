/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/01/25 18:40:21 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	char	*line;

	sig = 1;
	line = readline(("minishell $> "));
	handle_line(NULL);
	//exit(0);
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

void	setup_vars(int ac, char **av, char **env)
{
	vars.args.ac = ac;
	vars.args.av = av;
	vars.args.env = env;
	vars.last_exit_sat = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	setup_vars(ac, av, env);
	init_signals();
	while (1)
	{
		line = readline(("minishell $> "));
		if (line == NULL)
		{
			gt
			write(1, "exit\n", 6);
			exit(0);
		}
		if (*line != 0)
			add_history(line);
		handle_line(line);
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
