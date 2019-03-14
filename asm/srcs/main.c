/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 18:59:12 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/14 20:03:20 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int 		checkformat(char *name)
{
	char	*tmp;

	tmp = name;
	while (*tmp == '.' || *tmp == '/')
		tmp++;
	tmp = ft_strchr(tmp, '.');
	if (tmp && *(tmp + 1) == 's' && *(tmp + 2) == '\0' && *(tmp - 1))
		return (1);
	return (0);
}

int 		get_name(char **array, t_champ *champion)
{
	if (array)
	{
		if (!ft_strcmp(array[0], ".name") && array[1])
		{
			if (*(array[1]) == '"' && array[1][ft_strlen(array[1]) - 1] == '"')
			{
				if (array[2] && (*array[2]) != '#')
					return (0);
			}
			champion->name = ft_strsub(array[1], 1, ft_strlen(array[1]) - 2);
			if (ft_strlen(champion->name) > 129)
				return (0);
			return (1);
		}
		else if (!ft_strcmp(array[0], ".comment") && array[1])
		{
			if (*(array[1]) == '"' && array[1][ft_strlen(array[1]) - 1] == '"')
			{
				if (array[2] && (*array[2]) != '#')
					return (0);
			}
			champion->comment = ft_strsub(array[1], 1, ft_strlen(array[1]) - 2);
			if (ft_strlen(champion->name) > 2049)
				return (0);
			return (1);
		}
	}
	return (0);
}

int 		validity(char *name, t_champ *champion)
{
	int		fd;
	char	*line;
	int 	header;
	int 	end;

	header = 1;
	if (0 < (fd = open(name, O_RDONLY)))
	{
		while ((end = get_next_line(fd, &line)))
		{
			if (end == 2)
			{
				ft_strdel(&line);
				return (0);
			}
			if (*line == '#' || !ft_strcmp(line, ""))
			{
				ft_strdel(&line);
				continue;
			}
			else if (*line == '.' && header)
			{
				if (!get_name(ft_strsplit(line, '\t'), champion))
				{
					ft_strdel(&line);
					return (0);
				}
				if (champion->comment)
					header = 0;
			}
			else
				ft_strdel(&line);
		}
		return (1);
	}
	return (0);
}

void		initchamp(t_champ *champion)
{
	champion->name = NULL;
	champion->comment = NULL;
}

int			main(int argc, char **argv)
{
	t_champ *champion;

	if (argc == 2 && checkformat(argv[1]))
	{
		champion = (t_champ*)malloc(sizeof(t_champ));
		initchamp(champion);
		if (validity(argv[1], champion))
			ft_printf("%s\n%s\n", champion->name, champion->comment);
		else
			ft_printf("ERROR!\n");
	}
	else
		ft_printf(RED("Usage: ./asm champion.s\n"));
	return (0);
}

