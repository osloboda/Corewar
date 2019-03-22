/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 18:34:03 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/14 18:34:04 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *head, void *content, int (*f)(void *, void *))
{
	if (!f)
		return (NULL);
	while (head && !f(head->content, content))
		head = head->next;
	return (head);
}
