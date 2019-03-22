/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:32:58 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/30 16:33:00 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_power_pos(int nb, int power)
{
	long			res;
	unsigned int	pos_power;

	res = 1;
	if (power < 0)
		return (0);
	pos_power = power;
	while (pos_power-- > 0)
		res *= nb;
	return (res);
}
