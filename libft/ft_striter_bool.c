/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter_bool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 20:58:57 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/07 20:59:00 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_striter_bool(char *s, int (*f)(char))
{
	int	res;

	res = 0;
	if (s == NULL || f == NULL)
		return (res);
	while (*s)
	{
		res += (f(*s) != 0);
		s++;
	}
	return (res);
}
