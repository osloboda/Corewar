/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 17:53:00 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/16 17:53:36 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

int		linlist_len(t_linlist *head)
{
	int		i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
