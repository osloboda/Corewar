/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_new_link.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:45:01 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 19:45:01 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_linlist	*linlist_new_link(void *content, size_t cont_size)
{
	void		*new_cont;
	t_linlist	*new_list;

	new_list = (t_linlist *)malloc(sizeof(t_linlist));
	if (new_list == NULL)
		return (NULL);
	new_list->prev = NULL;
	new_list->next = NULL;
	new_list->content = content;
	new_list->content_size = cont_size;
	if (content == NULL)
		new_list->content_size = 0;
	return (new_list);
}
