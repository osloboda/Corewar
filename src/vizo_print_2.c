/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizo_print_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:05:15 by skarev            #+#    #+#             */
/*   Updated: 2019/03/22 14:05:16 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "vm.h"

void		print_speed(void)
{
	wattron(SC_W, A_BOLD);
	if (g_ncur->sec_lim == MIN_SPEED)
		mvwprintw(SC_W, 9, 3, "SPEED : [          ]            ");
	else if (g_ncur->sec_lim == 600000)
		mvwprintw(SC_W, 9, 3, "SPEED : [##        ]            ");
	else if (g_ncur->sec_lim == 700000)
		mvwprintw(SC_W, 9, 3, "SPEED : [####      ]            ");
	else if (g_ncur->sec_lim == 800000)
		mvwprintw(SC_W, 9, 3, "SPEED : [######    ]            ");
	else if (g_ncur->sec_lim == 900000)
		mvwprintw(SC_W, 9, 3, "SPEED : [########  ]            ");
	else if (g_ncur->sec_lim == MAX_SPEED)
		mvwprintw(SC_W, 9, 3, "SPEED : [##########] TURBOOOO!!!");
	wattroff(SC_W, A_BOLD);
	wrefresh(SC_W);
}

void		print_status(void)
{
	if (g_ncur->pause)
	{
		wattron(SC_W, COLOR_PAIR(3));
		mvwprintw(SC_W, 2, 10, "____  _____         _____   _____     ");
		mvwprintw(SC_W, 3, 10, "|   | |    | |    | |      |          ");
		mvwprintw(SC_W, 4, 10, "|__/  |____| |    | |____  |____      ");
		mvwprintw(SC_W, 5, 10, "|     |    | |    |      | |          ");
		mvwprintw(SC_W, 6, 10, "|     |    | |____|  ____| |_____     ");
		wattroff(SC_W, COLOR_PAIR(3));
	}
	else
	{
		wattron(SC_W, COLOR_PAIR(1));
		mvwprintw(SC_W, 2, 10, "____        _____                 ____ ");
		mvwprintw(SC_W, 3, 10, "|   | |     |    | \\  / | |\\   | |     ");
		mvwprintw(SC_W, 4, 10, "|__/  |     |____|  \\/  | | \\  | |  __ ");
		mvwprintw(SC_W, 5, 10, "|     |     |    |  |   | |  \\ | |   |");
		mvwprintw(SC_W, 6, 10, "|     |____ |    |  |   | |   \\| |___|");
		wattroff(SC_W, COLOR_PAIR(1));
	}
	wrefresh(SC_W);
}

void		print_winner(void)
{
	wattron(SC_W, A_BOLD);
	mvwprintw(SC_W, 46, 3, "Player %d", g_last_player->header->magic);
	wattron(SC_W, COLOR_PAIR(g_last_player->header->magic));
	mvwprintw(SC_W, 40, 8, "                                _____ ____");
	mvwprintw(SC_W, 41, 8, " \\          / || |\\   | |\\   | |      |   |");
	mvwprintw(SC_W, 42, 8, "  \\        /  || | \\  | | \\  | |____  |__/ ");
	mvwprintw(SC_W, 43, 8, "   \\  /\\  /   || |  \\ | |  \\ | |      |  \\");
	mvwprintw(SC_W, 44, 8, "    \\/  \\/    || |   \\| |   \\| |_____ |   \\");
	mvwprintw(SC_W, 47, 3, "%s", g_last_player->header->prog_name);
	wattroff(SC_W, A_BOLD);
	wattroff(SC_W, COLOR_PAIR(g_last_player->header->magic));
	if (g_ncur->music)
		system("killall afplay");
	wrefresh(SC_W);
}

void		print_players(void)
{
	int		i;

	i = 1;
	while (i - 1 < g_ncur->n_p)
	{
		mvwprintw(g_ncur->score, getcury(g_ncur->score) + 2, 3,\
											"Player -%d : ", i);
		wattron(g_ncur->score, COLOR_PAIR(i));
		mvwprintw(g_ncur->score, getcury(g_ncur->score), 16, "%s",\
						g_array_players[i - 1]->header->prog_name);
		wattroff(g_ncur->score, COLOR_PAIR(i));
		mvwprintw(g_ncur->score, getcury(g_ncur->score) + 1, 5,\
								"Last live :                 %d    ",\
								g_array_players[i - 1]->last_live);
		mvwprintw(g_ncur->score, getcury(g_ncur->score) + 1, 5,\
								"Lives in last period :      %d    ",\
								g_array_players[i - 1]->live_per_period);
		i++;
	}
}

void		print_score_board(void)
{
	wattron(g_ncur->score, A_BOLD);
	mvwprintw(g_ncur->score, 10, 3, "Cycle : %d", g_current_cyrcle);
	mvwprintw(g_ncur->score, 12, 3, "Processes : %d", g_ncur->n_c);
	print_players();
	mvwprintw(g_ncur->score, getcury(g_ncur->score) + 3, 3,\
						"CYCLE_TO_DIE : %d    ", g_cycle_to_die);
	mvwprintw(g_ncur->score, getcury(g_ncur->score) + 2, 3,\
							"CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(g_ncur->score, getcury(g_ncur->score) + 2, 3,\
								"NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(g_ncur->score, getcury(g_ncur->score) + 2, 3,\
							"MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(g_ncur->score, A_BOLD);
	wrefresh(g_ncur->score);
}
