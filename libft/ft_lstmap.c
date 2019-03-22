/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:20:09 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/30 15:21:41 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*old;
	t_list	*head;
	t_list	*current;

	if (!lst || !f)
		return (NULL);
	current = f(lst);
	head = ft_lstnew(current->content, current->content_size);
	old = head;
	lst = lst->next;
	while (lst)
	{
		current = f(lst);
		current = ft_lstnew(current->content, current->content_size);
		if (!current)
			return (NULL);
		old->next = current;
		old = old->next;
		lst = lst->next;
	}
	return (head);
}
