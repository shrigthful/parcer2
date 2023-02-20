/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/02/20 20:39:25 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	turn_env_list(char **env, t_list **env_lst)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back(env_lst, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
}

void	end_of_file(void)
{
	write(1, "exit\n", 5);
	if (g_vars.last_exit_sat == 1)
		exit(g_vars.last_exit_sat);
	exit(WEXITSTATUS(g_vars.last_exit_sat));
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_list		*lines;
	t_main_args	args;

	lines = NULL;
	setup_g_vars(ac, av, env, &args);
	init_signals();
	while (1337)
	{
		g_vars.line_handled = 0;
		line = get_line();
		if (line == NULL)
			end_of_file();
		if (*line != 0)
		{
			add_history(line);
			g_vars.line_handled = 1;
			handle_line(line, &args);
		}
		free(line);
	}
	return (0);
}
