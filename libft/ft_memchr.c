/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:46:54 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 19:27:06 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	t_byte	*str;
	t_byte	chr;
	size_t	i;

	chr = (t_byte)c;
	if (!s)
		return (NULL);
	i = 0;
	str = (t_byte *)s;
	while (i++ < n)
		if (str[i - 1] == chr)
			return ((void *)(s + i - 1));
	return (NULL);
}
