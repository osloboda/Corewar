/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnshift.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:57:10 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/26 21:43:41 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnshift(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	flag;

	i = 0;
	flag = 'n';
	if (!s1 || !s2)
		return (0);
	while (*s1 && flag == 'n')
	{
		j = 0;
		flag = 'y';
		while (s2[j] && flag == 'y')
		{
			if (s1[i] == s2[j])
				flag = 'n';
			j++;
		}
		if (flag == 'n')
			i++;
	}
	return (i);
}
