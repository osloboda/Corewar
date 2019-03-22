/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 21:05:36 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/28 15:08:45 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!needle || *needle == '\0' || !haystack)
		return ((char *)haystack);
	while (haystack[j])
	{
		i = 0;
		while (needle[i] && haystack[i + j] && haystack[i + j] == needle[i])
			i++;
		if (!needle[i])
			return ((char *)(haystack + j));
		j++;
	}
	return (NULL);
}
