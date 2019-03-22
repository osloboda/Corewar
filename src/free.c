/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 20:11:54 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/07 20:11:55 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	del_cursor(void *content, size_t size)
{
	size = 0;
	if (content)
		free(content);
	content = NULL;
}

void		main_free(void)
{
	int		i;

	i = -1;
	g_last_player = NULL;
	while (++i < MAX_PLAYERS)
		if (g_array_players[i])
		{
			if (PLAY_HEAD(i))
			{
				IF_FREE(PLAY_NAME(i));
				IF_FREE(PLAY_COMMENT(i));
				IF_FREE(PLAY_HEAD(i));
			}
			IF_FREE(PLAY_CODE(i));
			IF_FREE(g_array_players[i]);
			g_array_players[i] = NULL;
		}
	ft_lstdel(&g_all_cursor, del_cursor);
}
