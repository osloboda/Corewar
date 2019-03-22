/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:05:03 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/28 11:48:36 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	i = 0;
	if (!dst || !src)
		return (NULL);
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	while (i++ < len)
		s1[i - 1] = s2[i - 1];
	return (s1);
}
