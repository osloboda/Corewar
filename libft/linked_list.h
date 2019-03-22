/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:56:45 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 18:56:46 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "libft.h"

typedef struct			s_linlist
{
	void				*content;
	size_t				content_size;
	struct s_linlist	*prev;
	struct s_linlist	*next;
}						t_linlist;

void					linlist_del_el(t_linlist **alst,
							void (*del)(void *, size_t));
void					linlist_del_head(t_linlist **alst, t_linlist **tail,
							void (*del)(void *, size_t));
void					linlist_del_tail(t_linlist **alst, t_linlist **head,
							void (*del)(void *, size_t));
void					linlist_delall(t_linlist **alst, t_linlist **tail,
							void (*del)(void *, size_t));
int						linlist_is_emply(t_linlist *head);
void					linlist_iter(t_linlist *lst,
							void (*f)(t_linlist *elem));
t_linlist				*linlist_new_el(void *content, size_t cont_size);
t_linlist				*linlist_new_link(void *content, size_t cont_size);
void					linlist_push_head(t_linlist **alst,
							t_linlist **tail, t_linlist *new);
void					linlist_push_tail(t_linlist **alst,
							t_linlist **head, t_linlist *new);
t_linlist				*linlist_find(t_linlist *head, void *content,
							int (*f)(void *, void *));
void					*linlist_pop_tail(t_linlist **alst, t_linlist **head);
void					*linlist_pop_head(t_linlist **alst, t_linlist **tail);
int						linlist_len(t_linlist *head);
void					linlist_reverse(t_linlist **head, t_linlist **tail);

#endif
