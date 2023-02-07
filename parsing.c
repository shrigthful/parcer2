/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/02/07 14:04:56 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char s)
{
	if (s ==  '\f' || s ==  '\r' || s ==  '\v'
		|| s ==  '\n' || s ==  '\t' || s == ' ')
	{
		return (1);
	}
	return (0);
}

char	check_is_symbol(char s)
{
	if (s == '|')
		return ('|');
	if (s == '>')
		return('>');
	if (s == '<')
		return('>');
	return (0);
}

void	join_nodes(t_list **h)
{
	t_list	*todel;
	char	*new_str;
	int		space;

	todel = (*h)->next;
	space = ((t_range *)todel->content)->next_is_space;
	(*h)->next = todel->next;
	new_str = ft_strjoin(((t_range *)(*h)->content)->str,
		((t_range *)todel->content)->str);
	((t_range *)(*h)->content)->next_is_space = space;
	free(((t_range *)(*h)->content)->str);
	del_range(todel->content);
	free(todel);
	((t_range *)(*h)->content)->str = new_str;
}

void	join_lines(t_list **lst)
{
	t_list	*help;

	help = *lst;
	while (help)
	{
		if (help->next == NULL)
			return ;
		if (((t_range *)help->content)->type != 0
			&& ((t_range *)help->content)->next_is_space == 0)
		{
			if (((t_range *)help->next->content)->type != 0)
			{
				join_nodes(&help);
				continue ;
			}
		}
		help = help->next;
	}
}

void	print_ranges(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", ((t_range *)lst->content)->str);
		//printf("next is space %i	%s\n", ((t_range *)lst->content)->next_is_space , ((t_range *)lst->content)->str);
		lst = lst->next;
	}
}

void	print_io(t_list *lst)
{
	while (lst)
	{
		printf("	%s %s\n" ,((t_io *)lst->content)->type
			, ((t_io *)lst->content)->file);
		lst = lst->next;
	}
}

void	print_cmds(t_cmd *lst)
{
	printf("+++CMDS++++\n");
	while (lst)
	{
		printf("cmd = %s\n", lst->cmd);
		int	i = 0;
		while(lst->param[i])
		{
			printf("	%s\n", lst->param[i]);
			i++;
		}
		printf("infiles \n");
		print_io(lst->fles->input);
		printf("outfiles \n");
		print_io(lst->fles->output);
		printf("token '%s'\n",lst->token);
		lst = lst->next;
	}
}

void	handle_line(char *line)
{
	char	*line2;
	t_list	*lst;
	t_cmd	*cmd;

	line2 = ft_strtrim(line, " \f\v\n\r\t");
	if (line2 == NULL)
		exit(1);
	lst = qoutes_handling(line2);
	replace_env(&lst);//test + fix????????????????????
	join_lines(&lst);
	print_ranges(lst);
	cmd = conv_to_cmd(&lst);
	//if (cmd != NULL)
		//execute(cmd, &vars.args);
	//print_cmds(cmd);
	ft_lstclear2(&cmd, free);
	ft_lstclear(&lst, free);
	free(line2);
}
