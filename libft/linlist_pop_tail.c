/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_pop_tail.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:17:17 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/16 16:17:17 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	*linlist_pop_tail(t_linlist **alst, t_linlist **head)
{
	t_linlist	*old;
	void		*content;

	if (!alst || !head || !*alst)
		return (NULL);
	if (*alst == *head)
		*head = NULL;
	content = (*alst)->content;
	old = (*alst)->prev;
	free(*alst);
	*alst = old;
	if (*alst)
		(*alst)->next = NULL;
	return (content);
}
