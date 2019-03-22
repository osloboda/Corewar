/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_del_el.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:58:49 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 18:58:50 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	linlist_del_el(t_linlist **alst, void (*del)(void *, size_t))
{
	if (!alst || !*alst)
		return ;
	if (del)
		del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
