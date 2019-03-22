/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:36:51 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:45:06 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;

	if (!format)
		return (0);
	func_init();
	va_start(args, format);
	while (*format)
	{
		i = ft_strchr_or(format, '%');
		write(g_fd, format, i);
		format += i;
		g_total_len += i;
		if (*format == '%')
		{
			format += check_mask(format, args);
			if (g_type)
				g_total_len += g_funcs[(g_type - 'A') % ('a' - 'A')](args);
			else
				g_total_len += error_alarm(&format);
			clean_flags();
		}
	}
	va_end(args);
	return (g_total_len);
}
