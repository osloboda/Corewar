/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:20:50 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/22 12:57:55 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			doop(t_champ *champion, char **dest, int size)
{
	while (*champion->expect == '\t' || *champion->expect == ' ')
		champion->expect++;
	if (*champion->expect != '\0' && *champion->expect != '#'
			&& *champion->expect != ';')
		error(champion, "bad character");
	if ((int)ft_strlen(*dest) > size)
		error(champion, "name/comment lenght");
}

void			nameofcom(char **dest, t_champ *champion, int size)
{
	char		*tmp;

	if (*dest)
		error(champion, "doubles name");
	while (*champion->expect == '\t' || *champion->expect == ' ')
		champion->expect++;
	if (*champion->expect != '"')
		error(champion, "no name/comment");
	if (!ft_strchr(champion->expect + 1, '"'))
	{
		champion->expect++;
		tmp = ft_strdup(champion->expect);
		tmp = ft_new_strjoin(tmp, "\n");
		dop_noc(champion, &(*dest), tmp, "");
	}
	else
	{
		champion->expect++;
		*dest = ft_strsub(champion->expect, 0,
			ft_strchr(champion->expect, '"') - champion->expect);
		champion->expect = ft_strchr(champion->expect, '"') + 1;
	}
	doop(champion, &(*dest), size);
}

void			parse_token(t_champ *champion, int i)
{
	if (parse_label(champion))
		return ;
	while (i--)
	{
		if (ft_strnequ(champion->expect, OP(i).name, ft_strlen(OP(i).name)))
			parse_com(champion, i);
		else if (ft_strnequ(champion->expect, NAME_CMD_STRING, 5))
		{
			champion->expect += 5;
			nameofcom(&champion->name, champion, 128);
		}
		else if (ft_strnequ(champion->expect, COMMENT_CMD_STRING, 8))
		{
			champion->expect += 8;
			nameofcom(&champion->comment, champion, 2048);
		}
		else
			continue ;
		i = -2;
		break ;
	}
	if (i != -2)
		error(champion, "bad instruction");
}

int				dop_incode(unsigned char **inst,
	t_champ *champion, int *fd, int karet)
{
	unsigned		a;
	unsigned char	*tmp;

	a = 0;
	champion->out = ft_new_strjoin(champion->out, ".cor");
	*fd = open(champion->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_printf("Writing output program to %s\n", champion->out);
	karet = 4;
	tmp = ft_memalloc(132);
	ft_strcpy((char*)tmp, champion->name);
	a = to_big_endian(COREWAR_EXEC_MAGIC);
	ft_memcpy(*inst, &a, 4);
	a = 0;
	ft_memcpy(*inst + karet, tmp, 132);
	karet += 132;
	free(tmp);
	a = to_big_endian(champion->content_size);
	ft_memcpy(*inst + karet, &a, 4);
	karet += 4;
	tmp = ft_memalloc(COMMENT_LENGTH + 4);
	ft_memcpy((char*)tmp, champion->comment, ft_strlen(champion->comment));
	ft_memcpy(*inst + karet, tmp, COMMENT_LENGTH + 4);
	free(tmp);
	karet += COMMENT_LENGTH + 4;
	return (karet);
}

void			get_a(t_com *com, int *karet, unsigned char **inst)
{
	unsigned		a;
	int				d;
	char			**comarg;

	comarg = com->com_arg;
	d = 0;
	a = 0;
	while (d < 3)
	{
		if (*comarg && **comarg == 'r')
			a = a | REG_CODE;
		else if (*comarg && **comarg == '%')
			a = a | DIR_CODE;
		else if (*comarg && **comarg)
			a = a | IND_CODE;
		a = a << 2;
		comarg++;
		d++;
	}
	(*inst)[(*karet)++] = a;
}
