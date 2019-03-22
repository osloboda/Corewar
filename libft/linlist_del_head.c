/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_del_head.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:59:05 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 18:59:05 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	linlist_del_head(t_linlist **alst, t_linlist **tail,
							void (*del)(void *, size_t))
{
	t_linlist	*old;

	if (!alst || !del || !*alst)
		return ;
	if (*alst == *tail)
		*tail = NULL;
	old = ((*alst)->next);
	linlist_del_el(alst, del);
	*alst = old;
	if (*alst)
		(*alst)->prev = NULL;
}
