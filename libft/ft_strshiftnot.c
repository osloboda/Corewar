/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshiftnot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 16:02:47 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/28 16:28:21 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strshiftnot(char const *s, char c, size_t start)
{
	size_t	i;

	if (!s)
		return (0);
	i = start;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
