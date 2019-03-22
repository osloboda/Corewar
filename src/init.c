/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:29:39 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 13:30:04 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_header	*init_header(t_uint magic, char *prog_name,
						t_uint prog_size, char *comment)
{
	t_header	*header;

	header = (t_header *)malloc(sizeof(t_header));
	header->magic = magic;
	header->prog_size = prog_size;
	header->prog_name = prog_name;
	header->comment = comment;
	return (header);
}

t_player	*init_player(t_header *header, char *code)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	player->header = header;
	player->code = code;
	player->last_live = 0;
	player->live_per_period = 0;
	return (player);
}

t_cursor	*init_cursor(t_uint place, int whom)
{
	static	t_uint	id;
	t_cursor		*new_cursor;
	int				i;

	id++;
	new_cursor = (t_cursor *)malloc(sizeof(t_cursor));
	new_cursor->last_live = 0;
	new_cursor->id = id;
	new_cursor->op = 0;
	new_cursor->delay = 0;
	new_cursor->carry = 0;
	new_cursor->owner = whom;
	new_cursor->place = (MEM_SIZE + place) % MEM_SIZE;
	i = 0;
	new_cursor->reg[i] = -whom - 1;
	while (++i < REG_NUMBER)
		new_cursor->reg[i] = 0;
	return (new_cursor);
}

void		init_map(t_uint place, int whom)
{
	t_uint	i;

	i = 0;
	while (i < PLAY_SIZE(whom))
	{
		g_arena[(place + i) % MEM_SIZE] = PLAY_CODE(whom)[i];
		g_arena_color[(place + i) % MEM_SIZE] = whom + 1;
		i++;
	}
}

void		init_global(void)
{
	g_last_player = (!g_all_cursor) ? NULL :
		PLAYER(-((t_cursor *)g_all_cursor->content)->reg[0]);
	g_cycle_to_die = CYCLE_TO_DIE;
}
