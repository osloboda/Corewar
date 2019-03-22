/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_added.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 12:46:34 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:49:51 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_itoa_base(unsigned long long n, int base, char *res, int type)
{
	int	len;

	len = 0;
	g_dot--;
	if (n >= (unsigned long long)base || (g_is_dot && len < g_dot))
		len += ft_itoa_base(n / base, base, res, type);
	res[len++] = g_alpha[type][n % base];
	res[len] = '\0';
	return (len);
}

char		*ft_itoa_base_u(unsigned long long n, int base, int *len, int type)
{
	char	*res;

	res = (char *)malloc(sizeof(unsigned long long) * 8 + 1);
	if (n == 0 && g_is_dot && g_dot <= 0)
	{
		res[0] = '\0';
		*len = 0;
		return (res);
	}
	*len = ft_itoa_base(n, base, res, type);
	g_dot = 0;
	return (res);
}

char		*ft_itoa_base_s(long long n, int base, int *len, int type)
{
	char				*res;
	unsigned long long	nb;

	res = (char *)malloc(sizeof(long long) * 8 + 2);
	*len = 0;
	if (n == 0 && g_is_dot && g_dot <= 0)
	{
		res[0] = '\0' + (g_opts >> ('+' - ' ') & 1) * '+';
		res[1] = '\0';
		(*len) += (g_opts >> ('+' - ' ') & 1);
		return (res);
	}
	if (n < 0)
	{
		res[(*len)++] = '-';
		nb = -n;
	}
	else
	{
		nb = n;
		res[(*len)++] = '+';
	}
	(*len) += ft_itoa_base(nb, base, res + *len, type);
	g_dot = 0;
	return (res);
}
