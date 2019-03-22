/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_new_el.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:58:34 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 18:58:35 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_linlist	*linlist_new_el(void *content, size_t cont_size)
{
	void		*new_cont;
	t_linlist	*new_list;

	new_list = (t_linlist *)malloc(sizeof(t_linlist));
	if (new_list == NULL)
		return (NULL);
	new_list->prev = NULL;
	new_list->next = NULL;
	new_list->content = NULL;
	new_list->content_size = 0;
	if (content == NULL)
		return (new_list);
	new_cont = malloc(cont_size);
	if (new_cont == NULL)
		return (new_list);
	new_cont = ft_memcpy(new_cont, content, cont_size);
	new_list->content = new_cont;
	new_list->content_size = cont_size;
	return (new_list);
}
