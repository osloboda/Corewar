/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:57:48 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/26 21:43:24 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strshift(char const *s, char c, size_t start)
{
	size_t	i;

	if (!s)
		return (0);
	i = start;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}
