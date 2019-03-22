/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:35:38 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 17:20:53 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (i < n && s2[i])
		s1[len++] = s2[i++];
	s1[len] = '\0';
	return (s1);
}
