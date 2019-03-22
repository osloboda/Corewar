/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:58:05 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 18:25:01 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	t_byte	new[len];

	if (!dst || !src)
		return (NULL);
	ft_memcpy(new, src, len);
	ft_memcpy(dst, new, len);
	return (dst);
}
