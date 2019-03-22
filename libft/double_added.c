/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_added.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:19:47 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:45:39 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static long double	rounding(long double nb)
{
	int			index;
	long double	fract;

	index = g_dot;
	fract = 1.0;
	while (index-- > 0)
	{
		fract /= 10.0;
		nb *= 10.0;
		nb -= (int)nb;
	}
	if ((int)(nb * 10) >= 5)
		return (fract);
	return (0);
}

static void			ft_itoa_base_lf(long double n, char *res,
		int len, long double mult)
{
	int	i;

	i = -1;
	res[len] = '\0';
	while (++i < len)
	{
		res[i] = '0' + (int)(n / mult);
		n -= (int)(n / mult) * mult;
		mult /= 10;
	}
}

static void			ft_precision(char *precision, long double n)
{
	int	index;

	index = 0;
	while (index < g_dot)
	{
		n *= 10.0;
		precision[index++] = (int)n + '0';
		n -= (int)n;
	}
	precision[index] = '\0';
}

static int			ft_len_double(long double n, long double *mult)
{
	int	res;

	res = 1;
	*mult = 1.0;
	while (n > 9.5)
	{
		n /= 10.0;
		(*mult) *= 10;
		res++;
	}
	return (res);
}

char				*ft_itoa_floatting(long double n, int *len, char *precision)
{
	char		*res;
	long double	dot;
	long double	dec;
	long double	mult;

	res = (char *)malloc(500);
	*len = 0;
	if (n < 0)
	{
		res[(*len)++] = '-';
		n = -n;
	}
	else
		res[(*len)++] = '+';
	n += rounding(ft_modfl(n, &dot));
	dot = ft_modfl(n, &dec);
	(*len) += ft_len_double(dec, &mult);
	ft_itoa_base_lf(dec, res + 1, (*len) - 1, mult);
	ft_precision(precision, dot);
	return (res);
}
