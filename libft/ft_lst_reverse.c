/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:30:01 by ahavrius          #+#    #+#             */
/*   Updated: 2019/01/28 16:30:04 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_reverse(t_list *head)
{
	t_list	*current;
	t_list	*new;
	t_list	*prev;

	if (!head || !(head->next))
		return (head);
	prev = NULL;
	current = head;
	while (current != NULL)
	{
		new = current;
		current = current->next;
		new->next = prev;
		prev = new;
	}
	return (new);
}
