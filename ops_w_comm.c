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

static uint_t	atoui_bytecode(size_t start, size_t size)
{
    uint8_t	*str;
	uint_t	res;
	int		i;

	str = g_arena;
	res = 0;
	i = 0;
	start = (start + MEM_SIZE) % MEM_SIZE;
	while (size--)
		res += str[(start + size) % MEM_SIZE] << (8 * i++);
	return (res);
}

static int		skip_args(int arg, int dir_size, int max_arg)
{
	int	skip;

	skip = 0;
	if ((arg & 0xc0) == 0xc0)      //  11000000
		skip += 2;
	else if ((arg & 0x80) == 0x80) //  10000000
		skip += dir_size;
	else if ((arg & 0x40) == 0x40) //  01000000
		skip += 1;
	if (max_arg > 1)
	{
		if ((arg & 0x30) == 0x30) 	   //  00110000
			skip += 2;
		else if ((arg & 0x20) == 0x20) //  00100000
			skip += dir_size;
		else if ((arg & 0x10) == 0x10) //  00010000
			skip += 1;
	}
	if (max_arg > 2)
	{
		if ((arg & 0x0c) == 0x0c) 	   //  00001100
			skip += 2;
		else if ((arg & 0x08) == 0x08) //  00001000
			skip += dir_size;
		else if ((arg & 0x04) == 0x04) //  00000100
			skip += 1;
	}
	return (skip);
}

static int		valid_reg(t_cursor *cursor, int arg, int dir_size, int *shift)
{
	int	reg;
	int	skip;

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
** masks for arg1 - arg & 0xc0 ; arg2 - arg & 0x30 ; arg3 - arg & 0x0c
*/

static int		get_val(t_cursor *cursor, int *shift, int dir_size, uchar mask)
{
	int		val;
	short	ind;
	int		reg;

	val = 0;
	if (mask == 0xc0 || mask == 0x30  || mask == 0x0c)
	{
		ind = atoui_bytecode(((cursor->place + *shift) % MEM_SIZE), IND_SIZE);
		if (cursor->op == 13)
			val = atoui_bytecode(((cursor->place + ind) % MEM_SIZE), DIR_SIZE);
		else
			val = atoui_bytecode(((cursor->place + (ind % IDX_MOD)) % MEM_SIZE), DIR_SIZE);
		*shift += IND_SIZE;
        if (g_vflag & 0x04)
            ft_printf(" %d", val);
	}
	else if (mask == 0x80 || mask == 0x20 || mask == 0x08)
	{
		val = atoui_bytecode(((cursor->place + *shift) % MEM_SIZE), dir_size);
		*shift += dir_size;
		if (dir_size == 2)
            val = (short)val;
        if (g_vflag & 0x04)
            ft_printf(" %d", val);
	}
	else if (mask == 0x40 || mask == 0x10 || mask == 0x04)
	{
		reg = g_arena[(cursor->place + (*shift)++) % MEM_SIZE];
		val = cursor->reg[reg - 1];
        if ((g_vflag & 0x04) && (g_op_tab[cursor->op - 1].args_types[((uchar)~mask - 0xbf) / 30] == 1))
        	ft_printf(" r%d", reg);
        else if (g_vflag & 0x04)
        	ft_printf(" %d", val);
	}
	return (val);
}

static void		write_val(t_cursor *cursor, int *shift, int val, int mask)
{
	short	ind;
	int		reg;

	if (mask == 0xc0 || mask == 0x30  || mask == 0x0c)
	{
		ind = atoui_bytecode(((cursor->place + *shift) % MEM_SIZE), IND_SIZE);
		g_arena[(cursor->place + MEM_SIZE + (ind % IDX_MOD)) % MEM_SIZE] = val >> 24;
		g_arena[(cursor->place + MEM_SIZE + (ind % IDX_MOD) + 1) % MEM_SIZE] = val >> 16;
		g_arena[(cursor->place + MEM_SIZE + (ind % IDX_MOD) + 2) % MEM_SIZE] = val >> 8;
		g_arena[(cursor->place + MEM_SIZE + (ind % IDX_MOD) + 3) % MEM_SIZE] = val;
		*shift += IND_SIZE;
		if (g_vflag & 0x04)
			ft_printf(" %d\n", ind);
		g_arena_color[(cursor->place + MEM_SIZE +  (ind % IDX_MOD)) % MEM_SIZE] = cursor->owner;
		g_arena_color[(cursor->place + MEM_SIZE + (ind % IDX_MOD) + 1) % MEM_SIZE] = cursor->owner;
		g_arena_color[(cursor->place + MEM_SIZE + (ind % IDX_MOD) + 2) % MEM_SIZE] = cursor->owner;
		g_arena_color[(cursor->place + MEM_SIZE + (ind % IDX_MOD) + 3) % MEM_SIZE] = cursor->owner;
	}
	else if (mask == 0x40 || mask == 0x10 || mask == 0x04)
	{
		reg = g_arena[(cursor->place + (*shift)++) % MEM_SIZE];
		cursor->reg[reg - 1] = val;
        if ((g_vflag & 0x04) && (g_op_tab[cursor->op - 1].args_types[((uchar)~mask - 0xbf) / 30] == 1))
            ft_printf(" r%d\n", reg);
        else if (g_vflag & 0x04)
            ft_printf(" %d\n", reg);
	}
}

int				make_live(t_cursor *cursor, int arg, int *shift)
{
	int	val;
	int	i;

	(void)arg;
    if (g_vflag & 0x04)
        ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	// set the cursor's last_live = g_current_cyrcle
	cursor->last_live = g_current_cyrcle;
	g_live_per_cyrcle++;
	// read 4 bytes (DIR_SIZE) from arena
	*shift = 1;
	val = get_val(cursor, shift, 4, 0x80);
	if (g_vflag & 0x04)
		ft_printf("\n");

	// if the number equals to one of players, set him as g_last_player
	i = -val - 1;
	if (i >= 0 && i < MAX_PLAYERS && g_array_players[i] != NULL)
	{
		g_last_player = g_array_players[i];
		if (g_vflag & 0x01)
			ft_printf("Player %d (%s) is said to be alive\n", i + 1,
					  g_last_player->header->prog_name);
	}

	return (*shift);
}

int				make_ld(t_cursor *cursor, int arg, int *shift)
{
	int	val;

	*shift = 2;
	//  check that arg is correct and reg is correct too
	if (((arg & 0xf0) != 0x90 && (arg & 0xf0) != 0xd0) || !valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 2));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	//	identify arg type and take the value out of arg1, increase shift
	val = get_val(cursor, shift, 4, arg & 0xc0);

	//	if value == 0, carry = 1. else carry = 0
	if (val)
		cursor->carry = 0;
	else
		cursor->carry = 1;

	//	write value into registry that is an arg2, increase shift
	write_val(cursor, shift, val, arg & 0x30);
	return (*shift);
}

int				make_st(t_cursor *cursor, int arg, int *shift)
{
	int	val;
	int	reg;

	*shift = 2;
	//  check that arg is correct and regs are correct as well
	if (((arg & 0xf0) != 0x50 && (arg & 0xf0) != 0x70) || !valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 2));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	//  get the value from the arg1, increase shift
	val = get_val(cursor, shift, 4, arg & 0xc0);

	//  identify arg2 type and write value into it, increase shift
	write_val(cursor, shift, val, arg & 0x30);

	return (*shift);
}

int				make_add(t_cursor *cursor, int arg, int *shift)
{
	int reg;
	int	val1;
	int	val2;

	*shift = 2;
	//  check that arg is correct and regs are correct as well
	if (arg != 0x54 || !valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	// get the value of arg1, increase shift
	val1 = get_val(cursor, shift, 4, arg & 0xc0);

	// get the value of arg2, increase shift
	val2 = get_val(cursor, shift, 4, arg & 0x30);

	// write arg1 + arg2 into arg3, increase shift
	write_val(cursor, shift, val1 + val2, arg & 0x0c);

	// if arg1 + arg2 == 0, carry = 1, else carry = 0
	if (val1 + val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int				make_sub(t_cursor *cursor, int arg, int *shift)
{
	int reg;
	int	val1;
	int	val2;

	*shift = 2;
	//  check that arg is correct and regs are correct as well
	if (arg != 0x54 || !valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	// get the value of arg1, increase shift
	val1 = get_val(cursor, shift, 4, arg & 0xc0);

	// get the value of arg2, increase shift
	val2 = get_val(cursor, shift, 4, arg & 0x30);

	// write arg1 - arg2 into arg3, increase shift
	write_val(cursor, shift, val1 - val2, arg & 0x0c);

	// if arg1 - arg2 == 0, carry = 1, else carry = 0
	if (val1 - val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int				make_and(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;

	*shift = 2;
	// check that args are correct, and then that regs are too
	if (!(arg & 0xc0) || !(arg & 0x30) || (arg & 0x0c) != 0x04 ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	// determine the type of arg1, get value out of it, increase shift
	val1 = get_val(cursor, shift, 4, arg & 0xc0);

	// determine the type of arg2, get value out of it, increase shift
	val2 = get_val(cursor, shift, 4, arg & 0x30);

	// write val1 & val2 into arg3, deal with carry, increase shift
	write_val(cursor, shift, val1 & val2, arg & 0x0c);
	if (val1 & val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int				make_or(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;

	*shift = 2;
	// check that args are correct, and then that regs are too
	if (!(arg & 0xc0) || !(arg & 0x30) || (arg & 0x0c) != 0x04 ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	// determine the type of arg1, get value out of it, increase shift
	val1 = get_val(cursor, shift, 4, arg & 0xc0);

	// determine the type of arg2, get value out of it, increase shift
	val2 = get_val(cursor, shift, 4, arg & 0x30);

	// write val1 | val2 into arg3, deal with carry, increase shift
	write_val(cursor, shift, val1 | val2, arg & 0x0c);
	if (val1 | val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int				make_xor(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;

	*shift = 2;
	// check that args are correct, and then that regs are too
	if (!(arg & 0xc0) || !(arg & 0x30) || (arg & 0x0c) != 0x04 ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 3));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	// determine the type of arg1, get value out of it, increase shift
	val1 = get_val(cursor, shift, 4, arg & 0xc0);

	// determine the type of arg2, get value out of it, increase shift
	val2 = get_val(cursor, shift, 4, arg & 0x30);

	// write val1 ^ val2 into arg3, deal with carry, increase shift
	write_val(cursor, shift, val1 ^ val2, arg & 0x0c);
	if (val1 ^ val2)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);
}

int				make_zjmp(t_cursor *cursor, int arg, int *shift)
{
	int	val;

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	*shift = 1;
	// get the value of arg1
	val = get_val(cursor, shift, 2, 0x80);

	// jump on val if carry == 1
	if (cursor->carry == 1)
	{
		cursor->place = (cursor->place + MEM_SIZE + (val % IDX_MOD)) % MEM_SIZE;
		*shift = 0;
	}
	if (g_vflag & 0x04)
		ft_printf(" %s\n", cursor->carry ? "OK" : "FAILED");
	return (*shift);
}

int				make_ldi(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;
	int	val3;

	*shift = 2;
	// check that args are correct, and then that regs are too
	if (!(arg & 0xc0) || !(arg & 0x30) || (arg & 0x30) == 0x30 || (arg & 0x0c) != 0x04 ||
		!valid_reg(cursor, arg, 2, shift))
		return (*shift += skip_args(arg, 2, 3));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	// get the value of arg1 and arg2
	val1 = get_val(cursor, shift, 2, arg & 0xc0);
	val2 = get_val(cursor, shift, 2, arg & 0x30);

	// get the special val3 from -> (cursor->place + ((val1 + val2) % IDX_MOD)) % MEM_SIZE
	val3 = atoui_bytecode(((cursor->place + ((val1 + val2) % IDX_MOD)) % MEM_SIZE), 4);


	// write val3 into arg3
	write_val(cursor, shift, val3, arg & 0x0c);
    if (g_vflag & 0x04)
        ft_printf("%8| -> load from %d + %d = %d (with pc and mod %d)\n",
                  val1, val2, val1 + val2, cursor->place + ((val1 + val2) % IDX_MOD));
	return (*shift);
}

int				make_sti(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;
	int	val3;

	*shift = 2;
	// check that args are correct, and then that regs are too
	if ((arg & 0xc0) != 0x40 || !(arg & 0x30) || !(arg & 0x0c) || (arg & 0x0c) == 0x0c ||
		!valid_reg(cursor, arg, 2, shift))
		return (*shift += skip_args(arg, 2, 3));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	// get the value of arg1, arg2, arg3
	val1 = get_val(cursor, shift, 2, arg & 0xc0);
	val2 = get_val(cursor, shift, 2, arg & 0x30);
	val3 = get_val(cursor, shift, 2, arg & 0x0c);

	// write val1 into -> (cursor->place + ((val2 + val3) % IDX_MOD)) % MEM_SIZE
    if (g_vflag & 0x04)
        ft_printf("\n%8| -> store to %d + %d = %d (with pc and mod %d)\n",
                  val2, val3, val2 + val3, cursor->place + ((val2 + val3) % IDX_MOD));
	g_arena[(cursor->place + MEM_SIZE + ((val2 + val3) % IDX_MOD)) % MEM_SIZE] = val1 >> 24;
	g_arena[(cursor->place + MEM_SIZE + ((val2 + val3) % IDX_MOD) + 1) % MEM_SIZE] = val1 >> 16;
	g_arena[(cursor->place + MEM_SIZE + ((val2 + val3) % IDX_MOD) + 2) % MEM_SIZE] = val1 >> 8;
	g_arena[(cursor->place + MEM_SIZE + ((val2 + val3) % IDX_MOD) + 3) % MEM_SIZE] = val1;

	g_arena_color[(cursor->place + MEM_SIZE + ((val2 + val3) % IDX_MOD)) % MEM_SIZE] = cursor->owner;
	g_arena_color[(cursor->place + MEM_SIZE + ((val2 + val3) % IDX_MOD) + 1) % MEM_SIZE] = cursor->owner;
	g_arena_color[(cursor->place + MEM_SIZE + ((val2 + val3) % IDX_MOD) + 2) % MEM_SIZE] = cursor->owner;
	g_arena_color[(cursor->place + MEM_SIZE + ((val2 + val3) % IDX_MOD) + 3) % MEM_SIZE] = cursor->owner;
	return (*shift);
}

int				make_fork(t_cursor *cursor, int arg, int *shift)
{
	t_cursor	*new_cursor;
	short		val;
	int			i;

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	i = -1;
	*shift = 1;
	// get the value of arg1
	val = get_val(cursor, shift, 2, 0x80);
    if (g_vflag & 0x04)
        ft_printf(" (%d)\n", cursor->place + val % IDX_MOD);

	// make a copy of a cursor
	new_cursor = init_cursor((cursor->place + val % IDX_MOD) % MEM_SIZE, 0);
	while (++i < REG_NUMBER)
		new_cursor->reg[i] = cursor->reg[i];
	new_cursor->carry = cursor->carry;
	new_cursor->last_live = cursor->last_live;
    new_cursor->owner = cursor->owner;
	ft_lstadd(&g_all_cursor, ft_lstnew_link(new_cursor, 8));
	return (*shift);
}

int				make_lld(t_cursor *cursor, int arg, int *shift)
{
	int	val;

	*shift = 2;
	//  check that args are correct and reg is correct too
	if (((arg & 0xf0) != 0x90 && (arg & 0xf0) != 0xd0) || !valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 2));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	//	identify arg type and take the value out of arg1, increase shift
	val = get_val(cursor, shift, 4, arg & 0xc0);

	//	if value == 0, carry = 1. else carry = 0
	if (val)
		cursor->carry = 0;
	else
		cursor->carry = 1;

	//	write value into registry that is an arg2, increase shift
	write_val(cursor, shift, val, arg & 0x30);
	return (*shift);
}

int				make_lldi(t_cursor *cursor, int arg, int *shift)
{
	int	val1;
	int	val2;
	int	val3;

	*shift = 2;
	// check that args are correct, and then that regs are too
	if (!(arg & 0xc0) || !(arg & 0x30) || (arg & 0x30) == 0x30 || (arg & 0x0c) != 0x04 ||
		!valid_reg(cursor, arg, 2, shift))
		return (*shift += skip_args(arg, 2, 3));

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	// get the value of arg1 and arg2
	val1 = get_val(cursor, shift, 2, arg & 0xc0);
	val2 = get_val(cursor, shift, 2, arg & 0x30);

	// get the special val3 from -> (cursor->place + ((val1 + val2) % IDX_MOD)) % MEM_SIZE
	val3 = atoui_bytecode(((cursor->place + (val1 + val2)) % MEM_SIZE), 4);

	// write val3 into arg3
	write_val(cursor, shift, val3, arg & 0x0c);
    if (g_vflag & 0x04)
        ft_printf("%8| -> load from %d + %d = %d (with pc %d)\n",
                  val1, val2, val1 + val2, cursor->place + (val1 + val2));

	// deal with carry or not?
	if (val3)
		cursor->carry = 0;
	else
		cursor->carry = 1;
	return (*shift);

}

int				make_lfork(t_cursor *cursor, int arg, int *shift)
{
	t_cursor	*new_cursor;
	short		val;
	int			i;

	if (g_vflag & 0x04)
		ft_printf("P %4d | %s", cursor->id, g_op_tab[cursor->op - 1].name);
	i = -1;
	*shift = 1;
	// get the value of arg1
	val = get_val(cursor, shift, 2, 0x80);
    if (g_vflag & 0x04)
        ft_printf(" (%d)\n", cursor->place + val);

	// make a copy of a cursor
	new_cursor = init_cursor((cursor->place + val) % MEM_SIZE, 0);
	while (++i < REG_NUMBER)
		new_cursor->reg[i] = cursor->reg[i];
	new_cursor->carry = cursor->carry;
	new_cursor->last_live = cursor->last_live;
    new_cursor->owner = cursor->owner;
	ft_lstadd(&g_all_cursor, ft_lstnew_link(new_cursor, 8));
	return (*shift);
}

int				make_aff(t_cursor *cursor, int arg, int *shift)
{
	char    val;
	int     reg;

	val = 0;
	*shift = 2;
	// check that arg is correct, and then that reg is too
	if (!g_aflag || ((arg & 0xc0) != 0x40)  || !valid_reg(cursor, arg, 4, shift))
        return (*shift += skip_args(arg, 4, 1));

	// get the value from arg1
    reg = g_arena[(cursor->place + (*shift)++) % MEM_SIZE];
    val = cursor->reg[reg - 1];

	//print val as a char on the STD_OUT
	ft_printf("Aff: %c\n", val);
	return (*shift);
}


/*
** masks for arg1 - arg & 0xc0 ; arg2 - arg & 0x30 ; arg3 - arg & 0x0c ; T_DIR only - 0x80
*/




void		print_players(void)
{
	int			i;
	t_cursor	*cursor;

	i = -1;
	while (g_all_cursor->next)
	{
		cursor = (t_cursor *)g_all_cursor->content;
		ft_printf(
				"id - %d value - %02x, %02x %02x %02x %02x, place - %06p d - %d\n",
				cursor->id, g_arena[cursor->place], g_arena[cursor->place + 1],
				g_arena[cursor->place + 2], g_arena[cursor->place + 3],
				g_arena[cursor->place + 4], cursor->place, cursor->delay);
		g_all_cursor = g_all_cursor->next;
	}
	ft_printf("modulo - %hd\n", -32760 % MEM_SIZE);
}




























