/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:03:12 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 15:31:37 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*old;

	if (!alst)
		return ;
	while (*alst)
	{
		old = ((*alst)->next);
		ft_lstdelone(alst, del);
		*alst = old;
	}
	*alst = NULL;
}
