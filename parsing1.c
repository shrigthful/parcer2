/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:08:33 by jbalahce          #+#    #+#             */
/*   Updated: 2023/02/19 14:54:42 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_null_start(t_list *lst, char *line)
{
	if (*((t_range *)lst->content)->str == 0)
	{
		g_vars.last_exit_sat = 127;
		ft_lstclear(&lst, free);
		free(line);
		write(2, "invalid command\n", 16);
		return (1);
	}
	return (0);
}

void	handle_line(char *line, t_main_args *args)
{
	char	*line2;
	t_list	*lst;
	t_cmd	*cmd;
	int		num_cmds;

	if (*line == 0)
		return ;
	line2 = ft_strtrim(line, " \f\v\n\r\t");
	if (line2 == NULL)
		exit(1);
	lst = qoutes_handling(line);
	replace_env(&lst);
	join_lines(&lst);
	if (check_null_start(lst, line) != 0)
		return ;
	cmd = conv_to_cmd(&lst);
	num_cmds = size_cmd(cmd);
	if (cmd != NULL)
		execute(cmd, args, num_cmds);
	ft_lstclear2(&cmd, free);
	ft_lstclear(&lst, free);
	free(line2);
}
