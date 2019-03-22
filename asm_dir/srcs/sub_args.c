/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:23:18 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/22 12:55:14 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char			*label(char *line)
{
	char		*tmp;
	char		*name;

	tmp = ft_strchr(line, ':') + 1;
	while (*tmp && *tmp != '\t' && *tmp != ' ')
	{
		if (!ft_strchr(LABEL_CHARS, *tmp))
			return (NULL);
		tmp++;
	}
	name = ft_strsub(line, 0, tmp - line);
	while (*tmp == '\t' || *tmp == ' ')
		tmp++;
	if (*tmp)
		ft_strdel(&name);
	return (name);
}

t_com			*initvar(t_champ *champion, int i)
{
	t_com	*var;

	var = lstnew();
	var->com_arg = (char**)ft_memalloc(sizeof(char*) * 4);
	var->com_name = ft_strsub(champion->expect, 0,
		ft_strlen(OP(i).name));
	var->label = NULL;
	champion->expect += ft_strlen(OP(i).name);
	return (var);
}

char			**checksub(t_champ *champion, int i)
{
	char		*tmp;
	char		**mass;

	tmp = champion->expect;
	while (*tmp == '\t' || *tmp == ' ')
		tmp++;
	if (*tmp == 'r' && ft_atoi((tmp + 1)) >= 0
		&& ft_atoi((tmp + 1)) <= 99 && OP(i).args[0] & T_REG)
	{
		if (*champion->expect != ' ' && *champion->expect != '\t')
			error(champion, "bag separator");
	}
	if (ft_strchr(tmp, '#'))
		tmp = ft_strsub(tmp, 0, ft_strchr(tmp, '#') - tmp);
	else if (ft_strchr(tmp, ';'))
		tmp = ft_strsub(tmp, 0, ft_strchr(tmp, ';') - tmp);
	else
		tmp = ft_strdup(tmp);
	mass = ft_strsplit(tmp, ',');
	ft_strdel(&tmp);
	return (mass);
}

void			ifreg(char *tmp, t_com *var, t_champ *champion, int args)
{
	if (ft_isdigit(*(tmp + 2)))
		var->com_arg[args] = ft_strsub(tmp, 0, 3);
	else
		var->com_arg[args] = ft_strsub(tmp, 0, 2);
	tmp += ft_strlen(var->com_arg[args]);
	while (*tmp == '\t' || *tmp == ' ')
		tmp++;
	if (*tmp && *tmp != ';' && *tmp != '#')
		error(champion, "bag argument");
}

void			ifdir(char *tmp, t_com *var, t_champ *champion, int args)
{
	if (*(tmp + 1) == LABEL_CHAR)
	{
		if (!(var->com_arg[args] = label(tmp)))
			error(champion, "bad argument");
	}
	else if ((*(tmp + 1) == '-' && ft_isdigit(*(tmp + 2)))
		|| ft_isdigit(*(tmp + 1)))
	{
		tmp++;
		if (*tmp == '-')
			tmp++;
		while (ft_isdigit(*tmp))
			tmp++;
		var->com_arg[args] = ft_strsub(ft_strchr(var->mass[args], '%'),
			0, tmp - ft_strchr(var->mass[args], '%'));
		var->com_arg[args + 1] = NULL;
		while (*tmp == '\t' || *tmp == ' ')
			tmp++;
		if (*tmp)
			error(champion, "bad argument");
	}
	else
		error(champion, "bad argument");
}
