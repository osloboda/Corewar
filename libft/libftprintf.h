/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:53:53 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:20:46 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libmodf.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"

# define RED(string) "\x1b[31m" string "\x1b[0m"
# define BRED(string) "\x1b[1;31m" string "\x1b[0m"
# define GREEN(string) "\x1b[0;32m" string "\x1b[0m"
# define BGREEN(string) "\x1b[1;32m" string "\x1b[0m"
# define YELLOW(string) "\x1b[0;33m" string "\x1b[0m"
# define BYELLOW(string) "\x1b[01;33m" string "\x1b[0m"
# define BLUE(string) "\x1b[0;34m" string "\x1b[0m"
# define BBLUE(string) "\x1b[1;34m" string "\x1b[0m"
# define MAGENTA(string) "\x1b[0;35m" string "\x1b[0m"
# define BMAGENTA(string) "\x1b[1;35m" string "\x1b[0m"
# define CYAN(string) "\x1b[0;36m" string "\x1b[0m"
# define BCYAN(string) "\x1b[1;36m" string "\x1b[0m"

int		ft_strchr_or(const char *s, int c);
void	func_init(void);
void	clean_flags(void);
int		ft_atoi_simple(const char *str);
char	*ft_strcpy(char *dst, const char *src);
int		find_else(char *str, char c);

int		check_mask(const char *format, va_list args);
int		ft_printf(const char *format, ...);
char	*ft_itoa_base_s(long long n, int base, int *len, int type);
char	*ft_itoa_base_u(unsigned long long n, int base, int *len, int type);
int		format(char	*str_org, int len, char *precision);
char	*ft_itoa_floatting(long double n, int *len, char *precision);

int		ft_c(va_list args);
int		ft_s(va_list args);
int		ft_p(va_list args);
int		ft_d_i(va_list args);
int		ft_o_u_x(va_list args);
int		ft_f(va_list args);
int		ft_q(va_list args);
int		error_alarm(const char **c);

int		g_opts;
int		g_minlen;
int		g_dot;
char	g_is_dot;
char	g_flag;
char	g_type;

int		g_total_len;
int		g_fd;

char	g_alpha[2][17];
int		(*g_funcs[27])(va_list);

#endif
