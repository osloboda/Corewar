/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:44:20 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/24 16:48:53 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strinset(char const *s1, char const *s2)
{
	size_t	i;
	size_t	kol;
	size_t	j;
	char	flag;

	kol = 0;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i])
	{
		j = 0;
		flag = 'n';
		while (s2[j] && flag == 'n')
		{
			if (s1[i] == s2[j])
			{
				kol++;
				flag = 'y';
			}
			j++;
		}
		i++;
	}
	return (kol);
}
