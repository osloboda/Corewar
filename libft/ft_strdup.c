/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:01:59 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/28 13:16:48 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*new;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	new[len] = '\0';
	while (len-- > 0)
		new[len] = s1[len];
	return (new);
}
