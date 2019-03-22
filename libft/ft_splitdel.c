/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:37:13 by ahavrius          #+#    #+#             */
/*   Updated: 2019/02/14 17:37:14 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_splitdel(char **square)
{
	int	i;

	i = 0;
	while (square[i])
	{
		free(square[i]);
		++i;
	}
	free(square);
}
