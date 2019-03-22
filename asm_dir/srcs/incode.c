/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:19:13 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/21 15:19:16 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

unsigned int		to_big_endian(unsigned int x)
{
	return (((x >> 24) & 0x000000ff) |
			((x >> 8) & 0x0000ff00) |
			((x << 8) & 0x00ff0000) |
			((x << 24) & 0xff000000));
}

void				get_octal(char **comarg,
	unsigned char **inst, int *karet, int i)
{
	unsigned		a;

	if (*comarg && **comarg == 'r')
		(*inst)[(*karet)++] = (unsigned char)ft_atoi((*comarg) + 1);
	else if (*comarg && **comarg == '%')
	{
		if (OP(i).label == 0)
		{
			a = to_big_endian(ft_atoi((*comarg) + 1));
			ft_memcpy(*inst + *karet, &a, 4);
			*karet += 4;
		}
		else
		{
			a = to_big_endian((unsigned int)ft_atoi((*comarg) + 1)) >> 16;
			ft_memcpy(*inst + *karet, &a, 2);
			*karet += 2;
		}
	}
	else if (*comarg && **comarg)
	{
		a = to_big_endian((unsigned int)ft_atoi(*comarg)) >> 16;
		ft_memcpy(*inst + *karet, &a, 2);
		*karet += 2;
	}
}

void				inlabe(char **comarg,
	unsigned char **inst, int *karet, int i)
{
	unsigned		a;

	if (*comarg && **comarg == 'r')
		*inst[(*karet)++] = (unsigned char)ft_atoi((*comarg) + 1);
	else if (**comarg == '%')
	{
		if (OP(i).label == 0)
		{
			a = to_big_endian(ft_atoi((*comarg) + 1));
			ft_memcpy(*inst + *karet, &a, 4);
			*karet += 4;
		}
		else
		{
			a = to_big_endian(
					(unsigned int)ft_atoi((*comarg) + 1));
			a >>= 16;
			ft_memcpy(*inst + *karet, &a, 2);
			*karet += 2;
		}
	}
}

void				dopin(t_com *com, unsigned char **inst, int *karet, int i)
{
	int				d;
	char			**comarg;

	while (com && (i = 16))
	{
		while (i--)
		{
			if (ft_strnequ(com->com_name, OP(i).name, ft_strlen(OP(i).name)))
			{
				(*inst)[(*karet)++] = OP(i).opcode;
				comarg = com->com_arg;
				if (OP(i).octal)
				{
					get_a(com, &(*karet), &(*inst));
					d = -1;
					while (++d < 3)
						get_octal(&(*(comarg + d)), &(*inst), &(*karet), i);
				}
				else
					inlabe(&(*comarg), &(*inst), &(*karet), i);
				break ;
			}
		}
		com = com->next;
	}
}

void				incode(t_champ *champion)
{
	t_com			*com;
	int				karet;
	unsigned char	*inst;

	com = champion->token;
	inst = ft_memalloc(10048);
	karet = dop_incode(&inst, champion, &champion->fd, 0);
	dopin(com, &inst, &karet, 0);
	write(champion->fd, inst, karet);
	free(inst);
}
