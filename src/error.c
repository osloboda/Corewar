/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:15:52 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 14:16:39 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	drop_error(char *text_error)
{
	ft_printf("%s\n", text_error);
	main_free();
	exit(0);
}

void	help(char *name)
{
	ft_printf("Usage: %s [-vizo | -a -p -dump N -v N] [-n N ] <.cor>\n", name);
	ft_printf("###########################################################\n");
	ft_printf("");
	ft_printf("    -a        : Prints output from 'aff'\n");
	ft_printf("    -v N      : Verbosity levels, can be added together\n");
	ft_printf("                - 0 : Show only essentials\n");
	ft_printf("                - 1 : Show lives\n");
	ft_printf("                - 2 : Show cycles\n");
	ft_printf("                - 4 : Show operations\n");
	ft_printf("                - 8 : Show deaths\n");
	ft_printf("                - 16 : Show PC movements\n");
	ft_printf("    -dump N   : Dumps memory after N cycles then exits\n");
	ft_printf("    -p        : Shows alive cursors if dump is active\n");
	ft_printf("    -vizo     : Ncurses output mode\n");
	ft_printf("    -n        : Force define number of player\n");
	ft_printf("###########################################################\n");
	exit(0);
}
