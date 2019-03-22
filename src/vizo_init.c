/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizo_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:45:31 by skarev            #+#    #+#             */
/*   Updated: 2019/03/22 13:45:31 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "vm.h"

void		draw(void)
{
	key_hook();
	print_battle_field();
	print_cursor();
	print_live();
	print_score_board();
	usleep(1000000 - g_ncur->sec_lim);
}

void		init_ncurses(void)
{
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	cbreak();
	init_colors();
	g_ncur = (t_cur*)malloc(sizeof(t_cur));
	init_coord();
	g_ncur->field = newwin(66, 195, 0, 0);
	g_ncur->score = newwin(66, 59, 0, 195);
	g_ncur->sec_lim = 900000;
	g_ncur->n_p = count_players();
	g_ncur->pause = true;
	g_ncur->music = false;
	box(g_ncur->field, 0, 0);
	box(g_ncur->score, 0, 0);
	refresh();
	wrefresh(g_ncur->field);
	wrefresh(g_ncur->score);
}

void		init_coord(void)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	g_arena_coord = (int**)malloc(sizeof(int*) * 3);
	while (i < 3)
		g_arena_coord[i++] = (int*)malloc(sizeof(int) * MEM_SIZE);
	i = 0;
	x = 2;
	y = 1;
	while (i < MEM_SIZE)
	{
		if (y > 64)
			y = 1;
		if (x > 191)
		{
			x = 2;
			y += 1;
		}
		g_arena_coord[0][i] = y;
		g_arena_coord[1][i] = x;
		g_arena_coord[2][i++] = 0;
		x += 3;
	}
}

void		init_colors(void)
{
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_color(COLOR_GRAY, 400, 400, 400);
	init_pair(5, COLOR_GRAY, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_BLACK, COLOR_BLUE);
	init_pair(13, COLOR_BLACK, COLOR_RED);
	init_pair(14, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_GRAY, COLOR_GRAY);
	init_pair(101, COLOR_WHITE, COLOR_GREEN);
	init_pair(102, COLOR_WHITE, COLOR_BLUE);
	init_pair(103, COLOR_WHITE, COLOR_RED);
	init_pair(104, COLOR_WHITE, COLOR_CYAN);
}

void		dog_nail_1(int i)
{
	if (g_arena_coord[2][i] == 0)
		g_arena_coord[2][i] = 50;
	wattron(g_ncur->field, A_BOLD);
	wattron(g_ncur->field, COLOR_PAIR(g_arena_color[i] + 100));
	mvwprintw(g_ncur->field, g_arena_coord[0][i], g_arena_coord[1][i],\
												"%.2x", g_arena[i]);
	wattroff(g_ncur->field, COLOR_PAIR(g_arena_color[i] + 100));
	wattroff(g_ncur->field, A_BOLD);
}
