/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 11:21:24 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/15 11:22:05 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_link(void *content, size_t content_size)
{
	t_list	*newls;

	if (content == NULL)
		return (NULL);
	newls = (t_list *)malloc(sizeof(t_list));
	if (newls == NULL)
		return (NULL);
	newls->next = NULL;
	newls->content = content;
	newls->content_size = content_size;
	return (newls);
}
