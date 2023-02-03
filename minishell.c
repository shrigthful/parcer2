/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/02/03 18:07:07 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	sig = 1;
	exit(1);//code if read line dont exist
	write(1,"\n",1);
	//rl_replace_line("", 1); code id readline exits
	//rl_on_new_line();
	//rl_redisplay();
	vars.last_exit_sat = 1;
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
	t_list	*lines;

	lines = NULL;
	setup_vars(ac, av, env);
	init_signals();
/*
	while (1) code id readline exits
	{
		line = readline(("minishell $> "));
		if (line == NULL)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		if (*line != 0)
			add_history(line);
		handle_line(line);
		free(line);
	}
*/
//code if read line dont exist
	while (1)
	{
		write(1, "minishell >", 11);
		line = get_next_line(0);
		if (line != 0)
		{
			if (line[0] != '\n')
			{
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
