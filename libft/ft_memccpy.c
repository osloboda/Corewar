/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:23:01 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 15:23:26 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	t_byte	*s1;
	t_byte	*s2;
	t_byte	m;

	m = c;
	s1 = (t_byte *)dst;
	s2 = (t_byte *)src;
	if (!dst || !src)
		return (NULL);
	while (n--)
	{
		*s1++ = *s2;
		if (m == *s2++)
			return ((void *)s1);
	}
	return (NULL);
}
