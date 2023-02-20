/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:18:57 by jbalahce          #+#    #+#             */
/*   Updated: 2023/02/20 20:41:42 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_str2(int i, int j, char *line)
{
	char	*str;

	str = ft_substr(line, i, j - i + 1);
	if (str == NULL)
		exit(1);
	return (str);
}

void	insert(t_list **lst, char *str, int type, char space)
{
	t_range	*range;
	t_list	*new;

	range = malloc(sizeof(t_range));
	if (range == NULL)
		exit(1);
	range->next_is_space = space;
	range->type = type;
	range->str = str;
	new = ft_lstnew(range);
	if (new == NULL)
		exit(1);
	ft_lstadd_back(lst, new);
}

void	qoute_err(int *i, t_qoute *res)
{
	*i *= -1;
	res->err = 1;
}
