/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:16:39 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/22 13:00:29 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			insoct(t_com *com, int i)
{
	char		**comarg;
	int			d;

	com->com_size++;
	d = 0;
	comarg = com->com_arg;
	while (d < 3)
	{
		if (comarg && *comarg && **comarg == 'r')
			com->com_size++;
		else if (comarg && *comarg && **comarg == '%')
		{
			if (OP(i).label == 0)
				com->com_size += 4;
			else
				com->com_size += 2;
		}
		else if (*comarg && **comarg)
			com->com_size += 2;
		comarg++;
		d++;
	}
}

void			rlabe(t_com *com, int i)
{
	char		**comarg;

	comarg = com->com_arg;
	if (*comarg && **comarg == 'r')
		com->com_size++;
	else if (**comarg == '%')
	{
		if (OP(i).label == 0)
			com->com_size += 4;
		else
			com->com_size += 2;
	}
}

void			insize_com(t_champ *champion)
{
	t_com		*com;
	int			i;

	com = champion->token;
	com->com_size = 0;
	while (com)
	{
		i = 16;
		com->com_size = 0;
		while (i--)
		{
			if (ft_strnequ(com->com_name, OP(i).name,
				ft_strlen(OP(i).name)))
			{
				com->com_size++;
				if (OP(i).octal)
					insoct(com, i);
				else
					rlabe(com, i);
				break ;
			}
		}
		com = com->next;
	}
}

int				srdop(t_com *com, char *str, t_champ *champ, int res)
{
	t_com		*tmp;
	t_com		*label;

	tmp = com;
	while (tmp)
	{
		label = tmp->label;
		while (label)
		{
			if (!ft_strcmp(str, label->com_name))
				return (res);
			label = label->next;
		}
		res += tmp->com_size;
		tmp = tmp->next;
	}
	if ((label = champ->labelprev))
		while (label)
		{
			if (!ft_strcmp(str, label->com_name))
				return (res);
			label = label->next;
		}
	error(champ, "no such label");
	return (0);
}

int				search_label(t_com *com, char *str, t_champ *champ)
{
	t_com		*tmp;
	t_com		*label;
	int			res;

	tmp = com;
	res = 0;
	while (tmp)
	{
		label = tmp->label;
		while (label)
		{
			if (!ft_strcmp(str, label->com_name))
				return (res);
			label = label->next;
		}
		tmp = tmp->prev;
		if (tmp)
			res -= tmp->com_size;
	}
	return (srdop(com, str, champ, 0));
}
