/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:57:16 by skarev            #+#    #+#             */
/*   Updated: 2019/03/02 15:57:16 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "vm.h"

static void	atribute_on(int i)
{
	if (g_arena_color[i] == 0)
	{
		wattron(g_ncur->field, COLOR_PAIR(5));
		wattron(g_ncur->field, A_BOLD);
	}
	else if (g_arena_time[i])
	{
		wattron(g_ncur->field, COLOR_PAIR(g_arena_color[i]));
		wattron(g_ncur->field, A_BOLD);
	}
	else
		wattron(g_ncur->field, COLOR_PAIR(g_arena_color[i]));
}

static void	atribute_off(int i)
{
	if (g_arena_color[i] == 0)
	{
		wattroff(g_ncur->field, COLOR_PAIR(5));
		wattroff(g_ncur->field, A_BOLD);
	}
	else if (g_arena_time[i])
	{
		wattroff(g_ncur->field, COLOR_PAIR(g_arena_color[i]));
		wattroff(g_ncur->field, A_BOLD);
		g_arena_time[i] -= 1;
	}
	else
		wattroff(g_ncur->field, COLOR_PAIR(g_arena_color[i]));
}

void		print_battle_field(void)
{
	int		i;
	int		y;

	i = 0;
	y = 1;
	wmove(g_ncur->field, 2, 2);
	while (i < MEM_SIZE && y < 65)
	{
		if (getcurx(g_ncur->field) < 194)
		{
			atribute_on(i);
			mvwprintw(g_ncur->field, y, getcurx(g_ncur->field),\
											"%.2x ", g_arena[i]);
			atribute_off(i);
			i++;
		}
		else
		{
			wmove(g_ncur->field, getcury(g_ncur->field) + 1, 2);
			y++;
		}
	}
	wrefresh(g_ncur->field);
}

void		print_cursor(void)
{
	int		i;
	t_list	*head;

	i = 0;
	head = g_all_cursor;
	g_ncur->n_c = 0;
	while (head)
	{
		i = ((t_cursor*)head->content)->place;
		if (g_arena[i] == 1)
			dog_nail_1(i);
		else
		{
			wattron(g_ncur->field, COLOR_PAIR(g_arena_color[i] + 10));
			mvwprintw(g_ncur->field, g_arena_coord[0][i], g_arena_coord[1][i],\
														"%.2x", g_arena[i]);
			wattroff(g_ncur->field, COLOR_PAIR(g_arena_color[i] + 10));
		}
		g_ncur->n_c += 1;
		head = head->next;
	}
	wrefresh(g_ncur->field);
}

void		print_live(void)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (g_arena_coord[2][i] > 0)
		{
			wattron(g_ncur->field, A_BOLD);
			wattron(g_ncur->field, COLOR_PAIR(g_arena_color[i] + 100));
			mvwprintw(g_ncur->field, g_arena_coord[0][i], g_arena_coord[1][i],\
														"%.2x", g_arena[i]);
			wattroff(g_ncur->field, COLOR_PAIR(g_arena_color[i] + 100));
			wattroff(g_ncur->field, A_BOLD);
			g_arena_coord[2][i] -= 1;
		}
		i++;
	}
	wrefresh(g_ncur->field);
}
