/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_bytecode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:55:44 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 12:56:09 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int32_t	atoi_bytecode(const uint8_t *str, size_t size)
{
	uint32_t	res;
	char		sign;
	int			i;

	res = 0;
	i = 0;
	sing = str[0] & 0x80;
	while (size--)
		if (sign)
			res += (~str[size]) << (8 * i++);
		else
			res += str[size] << (8 * i++);
	res = (sign) ? ~res : res;
	return (res);
}
