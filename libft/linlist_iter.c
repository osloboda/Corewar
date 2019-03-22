/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_iter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:42:12 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/13 19:42:13 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	linlist_iter(t_linlist *lst, void (*f)(t_linlist *elem))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}
