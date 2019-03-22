/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:21:57 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 15:22:27 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	t_byte	*s11;
	t_byte	*s12;

	i = 0;
	if (s1 == s2 || n == 0 || !s1 || !s2)
		return (0);
	s11 = (t_byte *)s1;
	s12 = (t_byte *)s2;
	while (i < n && s11[i] == s12[i])
		i++;
	if (i == n)
		return (0);
	return (s11[i] - s12[i]);
}
