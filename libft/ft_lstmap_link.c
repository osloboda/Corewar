/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:07:05 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/21 15:07:06 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**the functoin reverse list before return. may use ft_lstreverse to get norm
*/

t_list	*ft_lstmap_link(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;

	head = NULL;
	while (lst && f)
	{
		ft_lstadd(&head, f(lst));
		lst = lst->next;
	}
	return (head);
}
