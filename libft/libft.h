/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchin <tchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 13:28:51 by tchin             #+#    #+#             */
/*   Updated: 2017/02/27 02:12:02 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include "get_next_line.h"

typedef struct		s_node
{
	void			*data;
	size_t			data_size;
	struct s_node	*next;
}					t_node;

typedef struct		s_list
{
	t_node			*head;
	t_node			*tail;
	int				size;
}					t_list;

int					ft_abs(int nbr);
void				*ft_memset(void *b, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strclen(const char *str, const char c);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *str, int start, int end);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, const char *base);
int					ft_iterative_power(int nb, int power);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void);
t_node				*ft_nodenew(void *data, size_t data_size);
void				ft_lstdelone(t_node *node, void (*del)(void *, size_t));
void				ft_lstdel(t_list *list, void (*del)(void *, size_t));
void				ft_lstipushfront(t_list *list, t_node *node);
void				ft_lstpushback(t_list *list, t_node *node);
t_node				*ft_lstfind(t_list *list, void *data_ref);
void				ft_lstforeach(t_list *list, void (*f)(void *));
void				ft_lstfree(t_list *list);
void				ft_lstfreeone(t_list *list, t_node *node);
void				ft_lstiter(t_list *list, void (*f)(t_node *node));
t_list				*ft_lstmap(t_list *list, t_node *(*f)(t_node *node));
void				ft_lstmerge(t_list *list1, t_list *list2);
t_node				*ft_lstremoveone(t_list *list, t_node *node);
t_node				*ft_lstswitch(t_list *src, t_list *dst, t_node *node);
int					ft_check_char(const char c, const char *str);
int					ft_nblen_base(const char *str, const char *base);
float				ft_degreetoradian(float degree);
float				ft_radiantodegree(float radian);

#endif
