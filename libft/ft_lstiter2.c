/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 18:15:38 by ahavrius          #+#    #+#             */
/*   Updated: 2019/01/28 18:15:39 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter2(t_list *lst, void *param, void (*f)(t_list *, void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst, param);
		lst = lst->next;
	}
}
