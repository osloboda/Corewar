/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:40:14 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/26 12:55:05 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_left(char const *s)
{
	size_t i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	return (i);
}

static size_t	ft_right(char const *s)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	while (i > 0 && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i--;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	finish;

	if (s == NULL)
		return (0);
	start = ft_left(s);
	finish = ft_right(s);
	if (finish < start)
		return (ft_strnew(0));
	return (ft_strsub(s + start, 0, finish - start + 1));
}
