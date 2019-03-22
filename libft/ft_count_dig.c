/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_dig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 18:08:12 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/24 19:04:10 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_dig(int n)
{
	unsigned int	i;
	int				count;

	count = 1;
	if (n < 0)
	{
		i = -n;
		count++;
	}
	else
		i = n;
	while (i > 9)
	{
		i /= 10;
		count++;
	}
	return (count);
}
