/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:23:23 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/07 17:23:24 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	choose_num(int amount_players, t_list **poor_players)
{
	int			i;
	t_list		*head;
	t_player	*cur_player;

	i = amount_players - 1;
	while (++i < MAX_PLAYERS)
		if (g_array_players[i] != NULL)
			drop_error(ERROR_PLAYERNUMBER);
	head = *poor_players;
	while (head != NULL)
	{
		i = 0;
		while (i < amount_players && g_array_players[i])
			i++;
		cur_player = (t_player *)head->content;
		cur_player->header->magic = i + 1;
		g_array_players[i] = cur_player;
		head = head->next;
	}
	ft_lstdel(poor_players, NULL);
}

void		intro(int amount_players, t_list **poor_players)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	*poor_players = ft_lst_reverse(*poor_players);
	choose_num(amount_players, poor_players);
	ft_printf("Introducing contestants...\n");
	while (++i < amount_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			PLAY_ID(i), PLAY_SIZE(i), PLAY_NAME(i), PLAY_COMMENT(i));
		init_map(j * MEM_SIZE / amount_players, i);
		ft_lstadd(&g_all_cursor, ft_lstnew_link(init_cursor(
								j * MEM_SIZE / amount_players, i), 8));
		j++;
	}
	init_global();
}

void		print_map(void)
{
	int		i;
	int		flag;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%06p : ", i);
		flag = 1;
		while (i < MEM_SIZE && flag)
		{
			ft_printf("%02x ", g_arena[i]);
			i++;
			flag = i % 32;
		}
		ft_printf("\n");
	}
}

void		print_v(t_cursor *cursor, int val, int reg, t_uchar mask)
{
	t_uchar	ch;

	ch = (t_uchar)~mask;
	if (g_vflag & 0x04)
	{
		if (mask == 0x40 || mask == 0x10 || mask == 0x04)
		{
			if (g_op_tab[cursor->op - 1].args_types[(ch - 0xbf) / 30] == 1)
				ft_printf(" r%d", reg);
			else
				ft_printf(" %d", val);
		}
		else
			ft_printf(" %d", val);
	}
}
