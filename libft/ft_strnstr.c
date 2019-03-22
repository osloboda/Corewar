/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 21:16:02 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 18:53:39 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	size;

	j = 0;
	if (!needle || !haystack || !*needle)
		return ((char *)(haystack));
	size = ft_strlen(needle);
	while (haystack[j] && size <= len)
	{
		if (ft_memcmp(haystack + j, needle, size) == 0)
			return ((char *)(haystack + j));
		j++;
		len--;
	}
	return (NULL);
}
