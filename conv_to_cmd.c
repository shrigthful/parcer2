/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/02/20 16:10:45 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_in_cmd(t_cmd **cmd, t_list **lst, t_help h)
{
	(*cmd)->param = get_params(h.params, *lst);
	(*cmd)->cmd = (*cmd)->param[0];
	(*cmd)->fles = malloc(sizeof(t_in_out));
	if ((*cmd)->fles == NULL)
		exit(0);
	(*cmd)->fles->errfile = NULL;
	(*cmd)->fles->input = get_input_files(h.infiles, *lst);
	(*cmd)->fles->output = get_output_files(h.outfiles, *lst);
	(*cmd)->fles->order = NULL;
	(*cmd)->next = NULL;
}

t_cmd	*get_node(t_list **lst)
{
	t_help	h;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		exit(1);
	init_help(&h);
	count_until_token(&h, *lst);
	insert_in_cmd(&cmd, lst, h);
	while (h.nodes > 0)
	{
		h.nodes--;
		*lst = (*lst)->next;
	}
	if (*lst != NULL)
	{
		cmd->token = ((t_range *)(*lst)->content)->str;
		*lst = (*lst)->next;
	}
	else
		cmd->token = NULL;
	return (cmd);
}


void	set_order(t_cmd	*cmds, t_list *lst)
{
	t_range	*range;

	while (lst)
	{
		range = (t_range *)lst->content;
		if (range->type == 0)
		{
			if (*range->str == '|')
				cmds = cmds->next;
			else
				insert_input_files(((t_range *)lst->next->content)->str,
					range->str, &cmds->fles->order);
		}
		lst = lst->next;
	}
}

t_cmd	*conv_to_cmd(t_list **lst)
{
	t_cmd	*cmds;
	t_list	*h;

	cmds = NULL;
	if (check_tokens(*lst) == 0)
	{
		ft_lstclear(lst, free_range_arr);
		return (NULL);
	}
	h = *lst;
	while (h)
		ft_lstadd_back2(&cmds, get_node(&h));
	set_order(cmds, *lst);
	return (cmds);
}
