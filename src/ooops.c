/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ooops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmerkulo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 17:01:08 by kmerkulo          #+#    #+#             */
/*   Updated: 2019/03/17 17:01:10 by kmerkulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		make_sti(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;
	int	val3;

	*shift = 2;
	if ((arg & 0xc0) != 0x40 || !(arg & 0x30) || !(arg & 0x0c) ||
		(arg & 0x0c) == 0x0c || !valid_reg(cursor, arg, 2, shift))
		return (*shift += skip_args(arg, 2, 3));
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	val1 = get_val(cursor, shift, 2, arg & 0xc0);
	val2 = get_val(cursor, shift, 2, arg & 0x30);
	val3 = get_val(cursor, shift, 2, arg & 0x0c);
	if (g_vflag & 0x04)
		ft_printf("\n%8| -> store to %d + %d = %d (with pc and mod %d)\n",
		val2, val3, val2 + val3, cursor->place + ((val2 + val3) % IDX_MOD));
	write_fun(cursor, val1, val2 + val3);
	return (*shift);
}

int		make_fork(t_cursor *cursor, int arg, int *shift)
{
	t_cursor	*new_cursor;
	short		val;
	int			i;

	(void)arg;
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	i = -1;
	*shift = 1;
	val = get_val(cursor, shift, 2, 0x80);
	if (g_vflag & 0x04)
		ft_printf(" (%d)\n", cursor->place + val % IDX_MOD);
	new_cursor = init_cursor((cursor->place + val % IDX_MOD) % MEM_SIZE, 0);
	while (++i < REG_NUMBER)
		new_cursor->reg[i] = cursor->reg[i];
	new_cursor->carry = cursor->carry;
	new_cursor->last_live = cursor->last_live;
	new_cursor->owner = cursor->owner;
	ft_lstadd(&g_all_cursor, ft_lstnew_link(new_cursor, 8));
	return (*shift);
}

int		make_lld(t_cursor *cursor, int arg, int *shift)
{
	int	val;

	*shift = 2;
	if (((arg & 0xf0) != 0x90 && (arg & 0xf0) != 0xd0) ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 2));
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	val = get_val(cursor, shift, 4, arg & 0xc0);
	if (val)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	write_val(cursor, shift, val, arg & 0x30);
	return (*shift);
}

int		make_lldi(t_cursor *cursor, int arg, int *shift)
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
	val3 = xtoi_bytecode(((cursor->place + (val1 + val2)) % MEM_SIZE), 4);
	write_val(cursor, shift, val3, arg & 0x0c);
	if (g_vflag & 0x04)
		ft_printf("%8| -> load from %d + %d = %d (with pc %d)\n",
		val1, val2, val1 + val2, cursor->place + (val1 + val2));
	if (val3)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int		make_lfork(t_cursor *cursor, int arg, int *shift)
{
	t_cursor	*new_cursor;
	short		val;
	int			i;

	(void)arg;
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	i = -1;
	*shift = 1;
	val = get_val(cursor, shift, 2, 0x80);
	if (g_vflag & 0x04)
		ft_printf(" (%d)\n", cursor->place + val);
	new_cursor = init_cursor((cursor->place + val) % MEM_SIZE, 0);
	while (++i < REG_NUMBER)
		new_cursor->reg[i] = cursor->reg[i];
	new_cursor->carry = cursor->carry;
	new_cursor->last_live = cursor->last_live;
	new_cursor->owner = cursor->owner;
	ft_lstadd(&g_all_cursor, ft_lstnew_link(new_cursor, 8));
	return (*shift);
}
