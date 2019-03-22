/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:05:16 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/14 17:05:17 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcountchr(char *str, char c)
{
	int		n;

	n = 0;
	while (str && *str)
	{
		n += (*str == c);
		str++;
	}
	return (n);
}
