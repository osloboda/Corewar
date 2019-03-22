/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_push_tail.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:58:00 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 18:58:01 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	linlist_push_tail(t_linlist **alst, t_linlist **head, t_linlist *new)
{
	if (!new || !alst || !head)
		return ;
	new->next = *alst;
	new->next = NULL;
	if (*alst)
		(*alst)->next = new;
	*alst = new;
	if (!*head)
		*head = new;
}
