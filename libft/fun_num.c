/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 13:12:30 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:48:37 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_d_i(va_list args)
{
	long long int	n;
	char			*str;
	int				len;

	len = 0;
	if (g_flag == 'h')
		n = (short int)va_arg(args, int);
	else if (g_flag == 'l')
		n = va_arg(args, long int);
	else if (g_flag == 'l' / 2)
		n = va_arg(args, long long int);
	else if (g_flag == 'h' / 2)
		n = (signed char)va_arg(args, int);
	else
		n = va_arg(args, int);
	str = ft_itoa_base_s(n, 10, &len, 0);
	return (format(str, len, NULL));
}

int	ft_o_u_x(va_list args)
{
	unsigned long long	n;
	char				*str;
	int					len;

	if (g_flag == 'h')
		n = (unsigned short int)va_arg(args, unsigned int);
	else if (g_flag == 'l')
		n = va_arg(args, unsigned long int);
	else if (g_flag == 'l' / 2)
		n = va_arg(args, unsigned long long int);
	else if (g_flag == 'h' / 2)
		n = (unsigned char)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);
	if (g_type == 'X')
		str = ft_itoa_base_u(n, 16, &len, 1);
	else if (g_type == 'x')
		str = ft_itoa_base_u(n, 16, &len, 0);
	else if (g_type == 'o')
		str = ft_itoa_base_u(n, 8, &len, 0);
	else if (g_type == 'u')
		str = ft_itoa_base_u(n, 10, &len, 0);
	else
		str = ft_itoa_base_u(n, 2, &len, 0);
	return (format(str, len, NULL));
}
