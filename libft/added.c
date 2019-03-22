/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   added.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:11:49 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 18:33:33 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		find_else(char *str, char c)
{
	while (*str && *str == c)
		str++;
	return (*str && *str != c);
}

int		ft_strchr_or(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int		ft_atoi_simple(const char *str)
{
	unsigned int	res;

	if (str == NULL)
		return (0);
	res = 0;
	while (*str && *str >= '0' && *str <= '9')
		res = 10 * res - '0' + *str++;
	return (res);
}

void	func_init(void)
{
	g_fd = 1;
	g_dot = -1;
	g_total_len = 0;
	ft_strcpy(g_alpha[0], "0123456789abcdef");
	ft_strcpy(g_alpha[1], "0123456789ABCDEF");
	g_funcs['c' - 'a'] = &ft_c;
	g_funcs['s' - 'a'] = &ft_s;
	g_funcs['p' - 'a'] = &ft_p;
	g_funcs['d' - 'a'] = &ft_d_i;
	g_funcs['i' - 'a'] = &ft_d_i;
	g_funcs['o' - 'a'] = &ft_o_u_x;
	g_funcs['u' - 'a'] = &ft_o_u_x;
	g_funcs['x' - 'a'] = &ft_o_u_x;
	g_funcs['b' - 'a'] = &ft_o_u_x;
	g_funcs['f' - 'a'] = &ft_f;
	g_funcs['q' - 'a'] = &ft_q;
}

void	clean_flags(void)
{
	g_opts = 0;
	g_is_dot = 0;
	g_minlen = 0;
	g_dot = -1;
	g_flag = 0;
	g_type = 0;
}
