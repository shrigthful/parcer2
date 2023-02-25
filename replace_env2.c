/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/02/22 21:44:47 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_str(t_list *lst)
{
	char	*new;
	t_range	*range;

	range = (t_range *)lst->content;
	if (ft_strlen(range->str) == 1)
	{
		free(range->str);
		range->str = ft_calloc(1, 1);
		return ;
	}
	new = ft_substr(range->str, 0, ft_strlen(range->str) - 1);
	if (new == NULL)
		exit(1);
	free(range->str);
	range->str = new;
}

void	del_dollar(t_list **lst)
{
	t_list	*help;
	t_range	*range;
	t_range	*range2;
	int		i;

	help = *lst;
	i = 0;
	while (help)
	{
		range = (t_range *)help->content;
		if (range->type == ' ' && range->next_is_space == 0
			&& range->str[ft_strlen(range->str) - 1] == '$')
		{
			if (help->next != NULL)
			{
				range2 = (t_range *)help->next->content;
				if (range2->type == '\'' || range2->type == '\"')
					replace_str(help);
			}
		}
		help = help->next;
	}
}
