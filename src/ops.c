/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmerkulo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:38:10 by kmerkulo          #+#    #+#             */
/*   Updated: 2019/03/07 15:38:12 by kmerkulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		make_live(t_cursor *cursor, int arg, int *shift)
{
	int	val;
	int	i;

	(void)arg;
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	cursor->last_live = g_current_cyrcle;
	g_live_per_cycle++;
	*shift = 1;
	val = get_val(cursor, shift, 4, 0x80);
	if (g_vflag & 0x04)
		ft_printf("\n");
	i = -val - 1;
	if (i >= 0 && i < MAX_PLAYERS && g_array_players[i] != NULL)
	{
		g_last_player = g_array_players[i];
		g_array_players[i]->last_live = g_current_cyrcle;
		g_array_players[i]->live_per_period++;
		if (g_vflag & 0x01)
			ft_printf("Player %d (%s) is said to be alive\n", i + 1,
					g_last_player->header->prog_name);
	}
	return (*shift);
}

int		make_ld(t_cursor *cursor, int arg, int *shift)
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

int		make_st(t_cursor *cursor, int arg, int *shift)
{
	int	val;

	*shift = 2;
	if (((arg & 0xf0) != 0x50 && (arg & 0xf0) != 0x70) ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 2));
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	val = get_val(cursor, shift, 4, arg & 0xc0);
	write_val(cursor, shift, val, arg & 0x30);
	return (*shift);
}

int		make_add(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;

	*shift = 2;
	if (arg != 0x54 || !valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	val1 = get_val(cursor, shift, 4, arg & 0xc0);
	val2 = get_val(cursor, shift, 4, arg & 0x30);
	write_val(cursor, shift, val1 + val2, arg & 0x0c);
	if (val1 + val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int		make_sub(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;

	*shift = 2;
	if (arg != 0x54 || !valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));
	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	val1 = get_val(cursor, shift, 4, arg & 0xc0);
	val2 = get_val(cursor, shift, 4, arg & 0x30);
	write_val(cursor, shift, val1 - val2, arg & 0x0c);
	if (val1 - val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}
