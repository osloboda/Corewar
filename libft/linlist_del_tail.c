/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_del_tail.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:59:13 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 18:59:14 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	linlist_del_tail(t_linlist **alst, t_linlist **head,
							void (*del)(void *, size_t))
{
	t_linlist	*old;

	if (!alst || !del || !*alst)
		return ;
	old = ((*alst)->prev);
	if (*alst == *head)
		*head = NULL;
	linlist_del_el(alst, del);
	*alst = old;
	if (*alst)
		(*alst)->next = NULL;
}
