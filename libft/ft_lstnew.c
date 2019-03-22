/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:11:55 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 16:32:05 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newls;
	void	*new_cont;

	newls = (t_list *)malloc(sizeof(t_list));
	if (newls == NULL)
		return (NULL);
	newls->next = NULL;
	if (content == NULL)
	{
		newls->content = NULL;
		newls->content_size = 0;
		return (newls);
	}
	new_cont = malloc(content_size);
	if (new_cont == NULL)
	{
		free(newls);
		return (NULL);
	}
	new_cont = ft_memcpy(new_cont, content, content_size);
	newls->content = new_cont;
	newls->content_size = content_size;
	return (newls);
}
