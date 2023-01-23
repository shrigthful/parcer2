/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:57:56 by monabid           #+#    #+#             */
/*   Updated: 2023/01/22 21:43:04 by monabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_range
{
	char	*str;
	int		type;
	int		next_is_space;
}	t_range;

typedef struct s_tab_cmd
{
	char	*cmd;
	char	**param;
}	t_tab_cmd;
// strings
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
//string4
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);
//string5

int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
//linked list
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
//read line
void	handle_line(char *line);
//step 1
char	check_is_symbol(char s);
int		is_space(char s);
t_list	*qoutes_handling(char *line);
void	replace_env(t_list **lst);

#endif
