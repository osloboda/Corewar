/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:00:11 by skarev            #+#    #+#             */
/*   Updated: 2019/03/22 14:00:11 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "vm.h"

void		key_hook(void)
{
	int		c;

	while (1)
	{
		c = getch();
		print_status();
		print_speed();
		key_hook_2(c);
		if (c == KEY_RIGHT)
			break ;
		if (g_ncur->pause)
			continue ;
		else
			break ;
	}
}

void		key_hook_2(int c)
{
	if (c == PAUSE_BUTTON && g_ncur->pause)
		g_ncur->pause = false;
	else if (c == PAUSE_BUTTON && !g_ncur->pause)
		g_ncur->pause = true;
	else if (c == SPEED_UP && g_ncur->sec_lim < MAX_SPEED)
		g_ncur->sec_lim += 100000;
	else if (c == SPEED_DOWN && g_ncur->sec_lim > MIN_SPEED)
		g_ncur->sec_lim -= 100000;
	else if (c == MUSIC && !g_ncur->music)
	{
		system("afplay ./sound/music.mp3&");
		g_ncur->music = true;
	}
	else if (c == MUSIC && g_ncur->music)
	{
		system("killall afplay");
		g_ncur->music = false;
	}
}

int			count_players(void)
{
	int		n;

	n = 0;
	while (g_array_players[n])
		n++;
	return (n);
}

void		end_vizo(void)
{
	print_winner();
	while (getch() != 27)
		;
	wclear(g_ncur->field);
	wclear(g_ncur->score);
	free_vizo();
	clear();
	echo();
	curs_set(1);
	endwin();
}

void		free_vizo(void)
{
	int		i;

	i = 0;
	while (i < 3)
		free(g_arena_coord[i++]);
	free(g_arena_coord);
	free(g_ncur);
}
