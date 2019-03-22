/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:50:24 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 13:50:25 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	read_file(char *file_name, int player_number, t_list **poor_players)
{
	char		c;
	t_player	*cur_player;
	int			file;

	if (ft_strcmp(file_name + ft_strlen(file_name) - 4, ".cor") != 0)
		drop_error(ERROR_FILECOR);
	file = open(file_name, O_RDONLY);
	if (file == -1)
		drop_error(ERROR_OPENFILE);
	cur_player = parce_bytecode(file, player_number);
	if (player_number == INT_MAX)
		ft_lstadd(poor_players, ft_lstnew_link(cur_player, 2));
	else if (g_array_players[player_number - 1])
		drop_error(ERROR_DOUBLEPLAYERS);
	else
		g_array_players[player_number - 1] = cur_player;
	if (read(file, &c, 1) > 0)
		drop_error(ERROR_TOOLONG);
	close(file);
}

static int	read_players(int argc, char **argv, t_list **poor_players)
{
	int			i;
	int			player_number;
	int			amount_players;

	i = -1;
	amount_players = 0;
	while (++i < argc)
	{
		player_number = INT_MAX;
		if (ft_strcmp(argv[i], "-n") == 0)
		{
			if (i + 2 >= argc)
				drop_error(ERROR_FLAGFORMAT);
			player_number = ft_atoi(argv[i + 1]);
			i += 2;
		}
		if (player_number != INT_MAX &&
				(player_number <= 0 || player_number > MAX_PLAYERS))
			drop_error(ERROR_PLAYERNUMBER);
		read_file(argv[i], player_number, poor_players);
		amount_players++;
	}
	if (amount_players > MAX_PLAYERS)
		drop_error(ERROR_NUMPLAYERS);
	return (amount_players);
}

static int	read_flags(int argc, char **argv)
{
	int		i;

	i = 0;
	g_dump = -1;
	while (++i < argc && (STR_EQ(argv[i], "-dump") || STR_EQ(argv[i], "-v") ||
STR_EQ(argv[i], "-p") || STR_EQ(argv[i], "-vizo") || STR_EQ(argv[i], "-a")))
	{
		if (ft_strcmp(argv[i], "-dump") == 0)
		{
			if (i + 1 >= argc || !IS_NUM(argv[i + 1]))
				drop_error(ERROR_FLAGFORMAT);
			g_dump = ft_atoi(argv[++i]);
		}
		else if (ft_strcmp(argv[i], "-v") == 0)
		{
			if (i + 1 >= argc || !IS_NUM(argv[i + 1]))
				drop_error(ERROR_FLAGFORMAT);
			g_vflag = ft_atoi(argv[++i]);
			g_vflag *= (g_vflag >= 0 && g_vflag <= 31);
		}
		g_vizo |= STR_EQ(argv[i], "-vizo");
		g_aflag |= STR_EQ(argv[i], "-a");
		g_pflag |= STR_EQ(argv[i], "-p");
	}
	return (i);
}

void		main_read(int argc, char **argv)
{
	int		shift;
	int		amount_players;
	t_list	*poor_players;

	poor_players = NULL;
	if (argc == 1)
		help(argv[0]);
	shift = read_flags(argc, argv);
	if (shift == argc)
		drop_error(ERROR_NOFILE);
	amount_players = read_players(argc - shift, &argv[shift], &poor_players);
	intro(amount_players, &poor_players);
}
