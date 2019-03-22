/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:57:03 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/17 16:57:04 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_swap(t_list *t1, t_list *t2)
{
	void	*i;
	size_t	t;

	i = t1->content;
	t1->content = t2->content;
	t2->content = i;
	t = t1->content_size;
	t1->content_size = t2->content_size;
	t2->content_size = t;
}

t_list			*ft_lstsort(t_list *lst, int (*cmp)(t_list *, t_list *))
{
	int		len;
	int		i;
	t_list	*start;

	if (!lst)
		return (lst);
	len = ft_lstlen(lst);
	i = 0;
	while (i < len)
	{
		start = lst;
		while (start->next)
		{
			if (!cmp(start, start->next))
				ft_swap(start, start->next);
			start = start->next;
		}
		i++;
	}
	return (lst);
}
