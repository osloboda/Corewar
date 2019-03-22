/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_push_head.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:57:47 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 18:57:49 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	linlist_push_head(t_linlist **alst, t_linlist **tail, t_linlist *new)
{
	if (!new || !alst || !tail)
		return ;
	new->next = *alst;
	new->prev = NULL;
	if (*alst)
		(*alst)->prev = new;
	*alst = new;
	if (!*tail)
		*tail = new;
}
