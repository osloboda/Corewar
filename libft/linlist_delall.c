/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_delall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:43:37 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 19:43:38 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	linlist_delall(t_linlist **alst, t_linlist **tail,
						void (*del)(void *, size_t))
{
	t_linlist	*old;

	if (!alst || !del)
		return ;
	while (*alst)
	{
		old = ((*alst)->next);
		linlist_del_el(alst, del);
		*alst = old;
	}
	*alst = NULL;
	*tail = NULL;
}
