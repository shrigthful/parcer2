/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_alpha.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:44:03 by monabid           #+#    #+#             */
/*   Updated: 2023/01/29 18:48:49 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end_ofvar(char *str, int i)
{
	int	j;

	j = i + 1;
	while (str[j])
	{
		if (ft_isalnum(str[j]) == 1)
			j++;
		else
			break ;
	}
	return (j);
}

int	replace_as_alpha2(char **str, int i, int type, int j)
{
	char	*start;
	char	*var_vale;
	char	*end;

	start = ft_substr(*str, 0, i);
	end = ft_substr(*str, i + 1, j);
	if (start == NULL || end == NULL)
		exit(1);
	//var_vale = getenv(end);
	var_vale = my_get_env(end, &vars.args);
	free(end);
	end = ft_substr(*str, j, ft_strlen(*str) - j);
	if (end == NULL)
		exit(1);
	free(*str);
	j = (int)ft_strlen(end);
	*str = group_strs(start, var_vale, end);
	return ((int)ft_strlen(*str) - j);
}

int	replace_as_alpha(char **str, int i, int type)
{
	char	*start;
	char	*var_vale;
	char	*end;
	int		j;

	j = get_end_ofvar(*str, i);
	if (i == 0 && j == ft_strlen(*str) && type == ' ')
	{
		start = NULL;
		end = ft_substr(*str, i + 1, j);
		if (end == NULL)
			exit(1);
		//var_vale = getenv(end);
		var_vale = my_get_env(end, &vars.args);
		free(end);
		end = NULL;
		if (var_vale == NULL)
		{
			free(*str);
			*str = NULL;
			return (-1);
		}
	}
	return (replace_as_alpha2(str, i, type, j));
}
