/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:27:43 by ahavrius          #+#    #+#             */
/*   Updated: 2019/01/28 16:37:00 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelnext(t_list *alst, void (*del)(void *, size_t))
{
	t_list*current;

	if (!alst || !del || !(alst->next))
		return ;
	current = alst->next;
	alst->next = current->next;
	ft_lstdelone(&current, del);
}
