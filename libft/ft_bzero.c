/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 19:07:38 by ahavrius          #+#    #+#             */
/*   Updated: 2018/10/28 11:22:06 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t size)
{
	size_t	i;
	char	*c;

	if (s == NULL)
		return ;
	i = 0;
	c = (char *)s;
	while (i < size)
	{
		c[i] = '\0';
		i++;
	}
}
