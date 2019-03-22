/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linlist_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 18:33:51 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/14 18:33:51 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_linlist	*linlist_find(t_linlist *head, void *content,
	int (*f)(void *, void *))
{
	if (!f)
		return (NULL);
	while (head && !f(head->content, content))
		head = head->next;
	return (head);
}
