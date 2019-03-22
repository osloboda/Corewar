/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 13:08:57 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:49:03 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_c(va_list args)
{
	char	c;
	char	*str;

	c = (char)va_arg(args, int);
	str = (char *)malloc(2);
	str[0] = c;
	str[1] = '\0';
	return (format(str, 1, NULL));
}

int		ft_q(va_list args)
{
	char	*str;

	str = (char *)malloc(2);
	str[0] = '%';
	if (args)
		str[1] = '\0';
	str[1] = '\0';
	return (format(str, 1, NULL));
}

int		ft_s(va_list args)
{
	char	*str;
	int		len;

	str = va_arg(args, char *);
	len = ft_strlen(str);
	if (str)
		return (format(str, (len > g_dot && g_is_dot) ? g_dot : len, NULL));
	str = (char *)malloc(7);
	ft_strcpy(str, "(null)");
	len = 6;
	len = format(str, (len > g_dot && g_is_dot) ? g_dot : len, NULL);
	free(str);
	return (len);
}

int		ft_p(va_list args)
{
	char	*ptr;
	int		len;
	char	*str;

	len = 0;
	ptr = (char *)va_arg(args, void *);
	str = ft_itoa_base_s((long long)ptr, 16, &len, 0);
	return (format(str, len, NULL));
}

int		error_alarm(const char **c)
{
	char	*str;

	if (**c == '\0')
		return (0);
	str = (char *)malloc(2);
	str[0] = **c;
	str[1] = '\0';
	g_type = 'c';
	(*c)++;
	return (format(str, 1, NULL));
}
