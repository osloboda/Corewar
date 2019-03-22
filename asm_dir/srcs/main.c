/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 18:59:12 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/22 12:56:49 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			checkl_dop(char **comarg,
		t_com *com, t_champ *champion)
{
	char		*tmp;

	if (ft_strchr(*comarg, ':'))
	{
		if (**comarg == '%')
		{
			tmp = ft_itoa(search_label(com, (*comarg) + 2, champion));
			ft_strdel(&(*comarg));
			*comarg = ft_strjoin("%", tmp);
			ft_strdel(&tmp);
		}
		else
		{
			tmp = ft_itoa(search_label(com, (*comarg) + 1, champion));
			ft_strdel(&(*comarg));
			*comarg = tmp;
		}
	}
}

void			checklabe(t_champ *champion)
{
	t_com		*com;
	char		**comarg;

	com = champion->token;
	while (com)
	{
		comarg = com->com_arg;
		champion->n = com->n;
		while (*comarg)
		{
			checkl_dop(comarg, com, champion);
			comarg++;
		}
		champion->content_size += com->com_size;
		com = com->next;
	}
}

void			validity(t_champ *champion)
{
	int			end;

	while ((end = get_next_lines(champion->fd, &champion->line)))
	{
		if (end == 2 && !*champion->line)
			error(champion, "unexpected end of input");
		champion->expect = champion->line;
		while (*champion->expect == '\t' || *champion->expect == ' ')
			champion->expect++;
		if (*champion->expect && *champion->expect != '#'
				&& *champion->expect != ';')
			parse_token(champion, 16);
		ft_strdel(&champion->line);
		champion->expect = NULL;
		champion->n++;
	}
	if (!champion->name || !champion->comment || !champion->token)
		(!champion->token) ? error(champion, "no code") :
		error(champion, "no name/comment");
	insize_com(champion);
	checklabe(champion);
	incode(champion);
}

void			initchamp(t_champ *champion, int fd)
{
	champion->name = NULL;
	champion->comment = NULL;
	champion->line = NULL;
	champion->token = NULL;
	champion->n = 1;
	champion->labelprev = NULL;
	champion->fd = fd;
}

int				main(int argc, char **argv)
{
	int			fd;
	t_champ		*champion;

	if (argc == 2 && checkformat(argv[1]) && (fd = open(argv[1], O_RDONLY)) > 0)
	{
		champion = (t_champ*)malloc(sizeof(t_champ));
		initchamp(champion, fd);
		champion->out = ft_strsub(argv[1], 0, ft_strlen(argv[1]) - 2);
		validity(champion);
	}
	else if (argc == 2)
		ft_printf("Can't read source file%s\n", argv[1]);
	else
		ft_printf(RED("Usage: ./asm <sourcefile.s>\n"));
	return (0);
}
