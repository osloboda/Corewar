/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:33:56 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:48:21 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_f(va_list args)
{
	long double	n;
	char		*dec;
	char		*dot;
	int			len;

	g_dot = (!g_is_dot) ? 6 : g_dot;
	dot = (char *)malloc(g_dot + 2);
	len = 0;
	if (g_flag == 'L')
		n = va_arg(args, long double);
	else
		n = va_arg(args, double);
	dec = ft_itoa_floatting(n, &len, dot + 1);
	if ((g_opts >> ('#' - ' ') & 1) || g_dot != 0)
	{
		dot[0] = '.';
		g_dot++;
	}
	else if (g_dot == 0)
		dot[0] = '\0';
	return (format(dec, len, dot));
}
