/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 15:20:18 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:45:56 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	write_format(int len, char *str)
{
	int		len_str;

	len_str = ft_strlen(str);
	while (len >= len_str)
	{
		write(g_fd, str, len_str);
		len -= len_str;
	}
	while (len-- > 0)
		write(g_fd, &str[0], 1);
	return (1);
}

static int	little_if(char **str, char *pre, int *len, int add_len)
{
	if ((g_opts >> ('#' - ' ') & 1) && g_is_dot && !(**str) && g_type == 'o')
		add_len += ft_strcpy(pre, "0") ? 1 : 0;
	if ((*str[0] == '-' || *str[0] == '+') && !ft_strchr("sc", g_type))
	{
		if (g_opts >> ('+' - ' ') & 1)
			pre[add_len++] = *str[0];
		else if (g_opts & 1)
			pre[add_len++] = (*str[0] == '-') ? '-' : ' ';
		else
		{
			pre[add_len] = (*str[0] == '-') ? '-' : '\0';
			add_len += (*str[0] == '-');
		}
		(*str)++;
		(*len)--;
	}
	return (add_len);
}

static int	write_pre(char **str, char *pre, int *len)
{
	int		add_len;

	add_len = 0;
	if (g_type == 'p')
		add_len += ft_strcpy(pre, "0x") ? 2 : 0;
	if ((g_opts >> ('#' - ' ') & 1) && find_else(*str, '0'))
	{
		if (g_type == 'o' && *str[0] != '0')
			add_len += ft_strcpy(pre, "0") ? 1 : 0;
		else if (g_type == 'x')
			add_len += ft_strcpy(pre, "0x") ? 2 : 0;
		else if (g_type == 'X')
			add_len += ft_strcpy(pre, "0X") ? 2 : 0;
	}
	add_len = little_if(str, pre, len, add_len);
	return (add_len);
}

static void	big_if(char *str, char *pre, char *precision, int len)
{
	if (g_opts >> ('-' - ' ') & 1)
	{
		write(g_fd, pre, ft_strlen(pre));
		write(g_fd, str, len);
		write(g_fd, precision, g_dot);
		if (g_minlen > ft_strlen(pre) + len + g_dot)
			write_format(g_minlen - (ft_strlen(pre) + g_dot + len), "       ");
		return ;
	}
	else if (g_opts >> ('0' - ' ') & 1)
	{
		write(g_fd, pre, ft_strlen(pre));
		if (g_minlen > ft_strlen(pre) + len + g_dot)
			write_format(g_minlen - (ft_strlen(pre) + g_dot + len), "0000000");
		write(g_fd, str, len);
		write(g_fd, precision, g_dot);
		return ;
	}
	if (g_minlen > ft_strlen(pre) + len + g_dot)
		write_format(g_minlen - (ft_strlen(pre) + g_dot + len), "     ");
	write(g_fd, pre, ft_strlen(pre));
	write(g_fd, str, len);
	write(g_fd, precision, g_dot);
}

int			format(char *str_org, int len, char *precision)
{
	int		add_len;
	char	*pre;
	char	*str;

	str = str_org;
	pre = ft_strnew(3);
	add_len = write_pre(&str, pre, &len);
	if (!precision)
		g_dot = 0;
	big_if(str, pre, precision, len);
	free(pre);
	if (g_type != 's')
		free(str_org);
	if (!precision)
		free(precision);
	return ((g_minlen > add_len + len + g_dot) ? g_minlen
	: add_len + g_dot + len);
}
