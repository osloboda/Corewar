/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 19:29:06 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/16 19:29:20 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	linlist_reverse(t_linlist **head, t_linlist **tail)
{
	t_linlist	*current;
	t_linlist	*change;

	if (!tail || !head || !*tail || !*head || !(*head)->next)
		return ;
	current = *tail;
	while (!current)
	{
		change = current->prev;
		current->prev = current->next;
		current->next = change;
		current = change;
	}
	change = *tail;
	*tail = *head;
	*head = change;
}
