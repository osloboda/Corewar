/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:44:55 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 18:06:24 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!dst || !src)
		return (0);
	while (i < size && dst[i])
		i++;
	len = i;
	i = 0;
	while (src[i] && i + len + 1 < size)
	{
		dst[i + len] = src[i];
		i++;
	}
	if (len < size)
		dst[i + len] = '\0';
	return (ft_strlen(src) + len);
}
