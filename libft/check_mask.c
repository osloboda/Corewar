/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mask.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 18:02:00 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:43:36 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	mask_num(const char *format, int *i_format, va_list args)
{
	if (format[*i_format] >= '0' && format[*i_format] <= '9')
	{
		g_minlen = ft_atoi_simple(format + *i_format);
		while (format[*i_format] >= '0' && format[*i_format] <= '9')
			(*i_format)++;
	}
	if (format[*i_format] == '.')
	{
		g_is_dot = 1;
		(*i_format)++;
		if (format[*i_format] == '*')
		{
			g_dot = va_arg(args, int);
			if (g_dot != 0 && !(g_dot *= (g_dot > 0)))
				g_is_dot = 0;
			(*i_format)++;
			return ;
		}
		g_dot = ft_atoi_simple(format + *i_format);
		while (format[*i_format] >= '0' && format[*i_format] <= '9')
			(*i_format)++;
	}
}

static void	mask_star(const char *format, int *i_format, va_list args)
{
	if (format[*i_format] != '*')
		return ;
	g_minlen = va_arg(args, int);
	(*i_format)++;
	if (g_minlen < 0)
	{
		if (!(g_opts >> ('-' - ' ') & 1))
			g_opts += 1 << ('-' - ' ');
		g_minlen *= -1;
	}
}

static void	mask_flags(const char *format, int *i_format)
{
	if (!format[*i_format])
		return ;
	if (format[*i_format] == 'l' && format[1 + *i_format] == format[*i_format])
	{
		g_flag = format[*i_format] / 2;
		(*i_format) += 2;
	}
	else if (format[*i_format] == 'l' || format[*i_format] == 'L')
	{
		g_flag = (g_flag != 'l' / 2) ? format[*i_format] : g_flag;
		(*i_format)++;
	}
	else if (format[*i_format] == 'h'
		&& format[1 + *i_format] == format[*i_format])
	{
		g_flag = (!g_flag) ? 'h' / 2 : g_flag;
		(*i_format) += 2;
	}
	else if (format[*i_format] == 'h')
	{
		g_flag = (g_flag && g_flag != 'h' / 2) ? g_flag : 'h';
		(*i_format)++;
	}
}

int			check_mask(const char *format, va_list args)
{
	int	i_format;

	i_format = 1;
	while (!g_type && ft_strchr("hlL#+-0* bcdefiopsuxX%.0123456789",
								format[i_format]) && format[i_format])
		if (ft_strchr("#+-0 ", format[i_format]))
		{
			if (!(g_opts >> (format[i_format] - ' ') & 1))
				g_opts += 1 << (format[i_format] - ' ');
			i_format++;
		}
		else if (format[i_format] == '*')
			mask_star(format, &i_format, args);
		else if (format[i_format] >= '0' && format[i_format] <= '9')
			mask_num(format, &i_format, args);
		else if (format[i_format] == '.')
			mask_num(format, &i_format, args);
		else if (ft_strchr("bcdefgikoprsuxX%", format[i_format]))
			g_type = format[i_format++];
		else
			mask_flags(format, &i_format);
	if (g_is_dot && !ft_strchr("fcs%", g_type) && (g_opts >> ('0' - ' ') & 1))
		g_opts -= 1 << ('0' - ' ');
	g_type = (g_type == '%') ? 'q' : g_type;
	return (i_format);
}
