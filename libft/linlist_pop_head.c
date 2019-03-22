/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_pop_head.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:17:37 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/16 16:17:38 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	*linlist_pop_head(t_linlist **alst, t_linlist **tail)
{
	t_linlist	*old;
	void		*content;

	if (!alst || !tail || !*alst)
		return (NULL);
	if (*alst == *tail)
		*tail = NULL;
	content = (*alst)->content;
	old = (*alst)->next;
	free(*alst);
	*alst = old;
	if (*alst)
		(*alst)->prev = NULL;
	return (content);
}
