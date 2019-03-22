/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmerkulo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:47:50 by kmerkulo          #+#    #+#             */
/*   Updated: 2019/03/17 16:47:55 by kmerkulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				skip_args(int arg, int dir_size, int max_arg)
{
	int	skip;

	skip = 0;
	if ((arg & 0xc0) == 0xc0)
		skip += 2;
	else if ((arg & 0x80) == 0x80)
		skip += dir_size;
	else if ((arg & 0x40) == 0x40)
		skip += 1;
	if (max_arg > 1 && (arg & 0x30) == 0x30)
		skip += 2;
	else if (max_arg > 1 && (arg & 0x20) == 0x20)
		skip += dir_size;
	else if (max_arg > 1 && (arg & 0x10) == 0x10)
		skip += 1;
	if (max_arg > 2 && (arg & 0x0c) == 0x0c)
		skip += 2;
	else if (max_arg > 2 && (arg & 0x08) == 0x08)
		skip += dir_size;
	else if (max_arg > 2 && (arg & 0x04) == 0x04)
		skip += 1;
	return (skip);
}

int				valid_reg(t_cursor *cursor, int arg, int dir_size, int *shift)
{
	int	reg;
	int	skip;

	reg = 0;
	if ((arg & 0xc0) == 0x40 && (g_op_tab[cursor->op - 1].args_types[0] & 0x01))
	{
		reg = g_arena[(cursor->place + *shift) % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
			return (0);
	}
	if ((arg & 0x30) == 0x10 && (g_op_tab[cursor->op - 1].args_types[1] & 0x01))
	{
		skip = skip_args(arg, dir_size, 1);
		reg = g_arena[(cursor->place + *shift + skip) % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
			return (0);
	}
	if ((arg & 0x0c) == 0x04 && (g_op_tab[cursor->op - 1].args_types[2] & 0x01))
	{
		skip = skip_args(arg, dir_size, 2);
		reg = g_arena[(cursor->place + *shift + skip) % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
			return (0);
	}
	return (reg);
}

/*
** masks for arg1 - arg & 0xc0; arg2 - arg & 0x30; arg3 - arg & 0x0c
*/

int				get_val(t_cursor *cursor, int *shift,
						int dir_size, t_uchar mask)
{
	int		val;
	short	ind;
	int		reg;

	reg = 0;
	if (mask == 0xc0 || mask == 0x30 || mask == 0x0c)
	{
		ind = xtoi_bytecode(((cursor->place + *shift) % MEM_SIZE), IND_SIZE);
		ind = (cursor->op == 13) ? ind : ind % IDX_MOD;
		val = xtoi_bytecode(((cursor->place + ind) % MEM_SIZE), DIR_SIZE);
		*shift += IND_SIZE;
	}
	else if (mask == 0x80 || mask == 0x20 || mask == 0x08)
	{
		val = xtoi_bytecode(((cursor->place + *shift) % MEM_SIZE), dir_size);
		*shift += dir_size;
		val = (dir_size == 2) ? (short)val : val;
	}
	else
	{
		reg = g_arena[(cursor->place + (*shift)++) % MEM_SIZE];
		val = cursor->reg[reg - 1];
	}
	print_v(cursor, val, reg, mask);
	return (val);
}

void			write_fun(t_cursor *cursor, int val, int ind)
{
	int	i;

	i = -1;
	while (++i < 4)
		W_ARENA(cursor->place + i, ind) = val >> (8 * (3 - i));
	i = -1;
	while (++i < 4)
		W_COLOR(cursor->place + i, ind) = cursor->owner;
	i = -1;
	while (++i < 4)
		W_TIME(cursor->place + i, ind) = 50;
}

void			write_val(t_cursor *cursor, int *shift, int val, int mask)
{
	short	ind;
	int		reg;

	if (mask == 0xc0 || mask == 0x30 || mask == 0x0c)
	{
		ind = xtoi_bytecode(((cursor->place + *shift) % MEM_SIZE), IND_SIZE);
		write_fun(cursor, val, ind);
		*shift += IND_SIZE;
		print_v(cursor, ind, 0, mask);
	}
	else if (mask == 0x40 || mask == 0x10 || mask == 0x04)
	{
		reg = g_arena[(cursor->place + (*shift)++) % MEM_SIZE];
		cursor->reg[reg - 1] = val;
		print_v(cursor, reg, reg, mask);
	}
	if (g_vflag & 0x04)
		ft_printf("\n");
}
