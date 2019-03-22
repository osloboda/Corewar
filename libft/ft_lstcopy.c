/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:10:43 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/21 15:10:45 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**the functoin reverse list before return. may use ft_lstreverse to get norm
*/

t_list			*ft_lstcopy(t_list *lst)
{
	t_list	*head;

	head = NULL;
	while (lst)
	{
		ft_lstadd(&head, ft_lstnew_link(lst->content, lst->content_size));
		lst = lst->next;
	}
	return (head);
}
