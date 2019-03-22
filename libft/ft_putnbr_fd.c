/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 18:44:15 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/30 16:10:55 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (-(long)n > 9)
			ft_putnbr_fd((-(long)n) / 10, fd);
		ft_putchar_fd((-(long)n) % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}
