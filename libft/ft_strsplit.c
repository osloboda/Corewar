/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:34:30 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 16:35:53 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_skipcount(char const *s, char c)
{
	size_t	count;

	count = 0;
	s += ft_strshift(s, c, 0);
	while (*s)
	{
		if (*s != c)
		{
			s += ft_strshiftnot(s, c, 0);
			count++;
		}
		s++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	j;
	size_t	k;
	size_t	i;
	size_t	len;

	k = 0;
	if (s == NULL)
		return (NULL);
	i = ft_strshift(s, c, 0);
	tab = (char **)malloc(sizeof(char *) * (ft_skipcount(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (s[i])
	{
		len = ft_strshiftnot(s, c, i) - i;
		j = 0;
		tab[k] = (char *)malloc(len + 1);
		while (len > j)
			tab[k][j++] = s[i++];
		tab[k++][j] = '\0';
		i = ft_strshift(s, c, i);
	}
	tab[k] = 0;
	return (tab);
}
