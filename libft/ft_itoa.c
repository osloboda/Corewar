/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 18:14:28 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/28 16:25:56 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nn;
	int				i;

	i = ft_count_dig(n);
	str = (char *)malloc(i + 1);
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	i--;
	if (n < 0)
	{
		nn = -n;
		str[0] = '-';
	}
	else
		nn = n;
	while (nn > 9)
	{
		str[i] = nn % 10 + '0';
		nn /= 10;
		i--;
	}
	str[i] = nn + '0';
	return (str);
}
