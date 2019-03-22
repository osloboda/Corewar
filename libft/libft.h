/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:02:43 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/30 16:30:54 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "libmodf.h"
# include "libftprintf.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "linked_list.h"
# include "get_next_line.h"

typedef	unsigned char	t_byte;

int					ft_count_dig(int n);
size_t				ft_strshiftnot(char const *s, char c, size_t start);
long				ft_power_pos(int nb, int power);

void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(char c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_bzero(void *s, size_t size);
size_t				ft_strlen (const char *str);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_strcmp(const char *str1, const char *str2);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_new_strjoin(char *str1, char const *str2);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (f)(unsigned int, char *));
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

int					ft_striter_bool(char *s, int (*f)(char));
size_t				ft_strnshift(char const *s1, char const *s2);
size_t				ft_strshift(char const *s, char c, size_t start);
int					ft_strcountchr(char *str, char c);
void				ft_splitdel(char **square);
int					ft_atoi_base(const char *str, int str_base);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *));
void				ft_lstiter2(t_list *lst, void *param,
									void (*f)(t_list *, void *));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstmap_link(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstsort(t_list *lst, int (*cmp)(t_list *, t_list *));
t_list				*ft_lstcopy(t_list *lst);

t_list				*ft_lstnew_link(void *content, size_t content_size);
t_list				*ft_lst_reverse(t_list *head);
int					ft_lstlen(t_list *head);
void				ft_lstdelnext(t_list *alst, void (*del)(void *, size_t));
t_list				*ft_lstfind(t_list *head, void *content,
						int (*f)(void *, void *));

#endif
