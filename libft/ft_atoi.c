/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:24:45 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/29 18:13:46 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	if (str == NULL)
		return (0);
	str += ft_strnshift(str, " \n\t\f\r\v");
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	res = 0;
	while (*str && ft_isdigit(*str))
		res = 10 * res - '0' + *str++;
	return (res * sign);
}
