/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:17:32 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 15:33:22 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	len++;
	if (!dst || !src)
		return (NULL);
	while (--len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (len--)
		dst[i++] = '\0';
	return (dst);
}
