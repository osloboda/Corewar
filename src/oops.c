/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oops.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmerkulo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 17:00:55 by kmerkulo          #+#    #+#             */
/*   Updated: 2019/03/17 17:00:57 by kmerkulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		make_and(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;

	*shift = 2;
	if (!(arg & 0xc0) || !(arg & 0x30) || (arg & 0x0c) != 0x04 ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	val1 = get_val(cursor, shift, 4, arg & 0xc0);
	val2 = get_val(cursor, shift, 4, arg & 0x30);
	write_val(cursor, shift, val1 & val2, arg & 0x0c);
	if (val1 & val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int		make_or(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;

	*shift = 2;
	if (!(arg & 0xc0) || !(arg & 0x30) || (arg & 0x0c) != 0x04 ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	val1 = get_val(cursor, shift, 4, arg & 0xc0);
	val2 = get_val(cursor, shift, 4, arg & 0x30);
	write_val(cursor, shift, val1 | val2, arg & 0x0c);
	if (val1 | val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int		make_xor(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;

	*shift = 2;
	if (!(arg & 0xc0) || !(arg & 0x30) || (arg & 0x0c) != 0x04 ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	val1 = get_val(cursor, shift, 4, arg & 0xc0);
	val2 = get_val(cursor, shift, 4, arg & 0x30);
	write_val(cursor, shift, val1 ^ val2, arg & 0x0c);
	if (val1 ^ val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int		make_zjmp(t_cursor *cursor, int arg, int *shift)
{
	int	val;

	(void)arg;
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	*shift = 1;
	val = get_val(cursor, shift, 2, 0x80);
	if (cursor->carry == 1)
	{
		cursor->place = (cursor->place + MEM_SIZE + (val % IDX_MOD)) % MEM_SIZE;
		*shift = 0;
	}
	if (g_vflag & 0x04)
		ft_printf(" %s\n", cursor->carry ? "OK" : "FAILED");
	return (*shift);
}

int		make_ldi(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;
	int	val3;

	*shift = 2;
	if (!(arg & 0xc0) || !(arg & 0x30) || (arg & 0x30) == 0x30 ||
		(arg & 0x0c) != 0x04 || !valid_reg(cursor, arg, 2, shift))
		return (*shift += skip_args(arg, 2, 3));
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	val1 = get_val(cursor, shift, 2, arg & 0xc0);
	val2 = get_val(cursor, shift, 2, arg & 0x30);
	val3 = xtoi_bytecode(((cursor->place + ((val1 + val2) % IDX_MOD))
			% MEM_SIZE), 4);
	write_val(cursor, shift, val3, arg & 0x0c);
	if (g_vflag & 0x04)
		ft_printf("%8| -> load from %d + %d = %d (with pc and mod %d)\n",
		val1, val2, val1 + val2, cursor->place + ((val1 + val2) % IDX_MOD));
	return (*shift);
}
