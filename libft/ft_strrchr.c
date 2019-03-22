/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 21:01:54 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/28 12:02:59 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	while (len > 0 && s[len - 1] != c)
		len--;
	if (len == 0)
		return (NULL);
	return ((char *)(s + len - 1));
}
