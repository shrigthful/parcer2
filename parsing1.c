/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:08:33 by jbalahce          #+#    #+#             */
/*   Updated: 2023/02/24 19:06:11 by monabid          ###   ########.fr       */
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

void	qoutes_stop(char *line2, t_list *lst)
{
	ft_lstclear(&lst, free_range_arr);
	free(line2);
}

void	range_print(t_list *lst)
{
	t_range *range;

	while (lst)
	{
		range = (t_range *)lst->content;
		printf("%s :'%c' :%i :%i\n", range->str, range->type, range->next_is_space, range->expendable);
		lst = lst->next;
	}

}

void	set_expandale2(t_list *lst)
{
	t_range *range;

	while (lst)
	{
		range = (t_range *)lst->content;
		range->expendable = 1;
		if (range->next_is_space == 1)
			break;
		lst = lst->next;
	}

}

void	set_expandale(t_list **lst)
{
	t_list	*help;
	t_range *range;

	del_dollar(lst);
	help = *lst;
	while (help)
	{
		range = (t_range *)help->content;
		if (range->type == 0 && ft_strcmp("<<", range->str) == 0
			&& help->next != NULL)
		{
			set_expandale2(help);
		}
		help = help->next;
	}
}

void	handle_line(char *line, t_main_args *args)
{
	char	*line2;
	t_cmd	*cmd;
	t_qoute	res;

	if (*line == 0)
		return ;
	line2 = ft_strtrim(line, " \f\v\n\r\t");
	if (line2 == NULL)
		exit(1);
	res = qoutes_handling(line);
	if (res.err == 1)
	{
		qoutes_stop(line2, res.lst);
		return ;
	}
	set_expandale(&res.lst);
	range_print(res.lst);
	replace_env(&res.lst);
	join_lines(&res.lst);
	cmd = conv_to_cmd(&res.lst);
	if (cmd != NULL)
		execute(cmd, args, size_cmd(cmd));
	free(line2);
	ft_lstclear2(&cmd, free);
	ft_lstclear(&res.lst, free);
}
