/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:22:10 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/22 12:55:43 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			ifindir(char *tmp, t_com *var, t_champ *champion, int args)
{
	if (*tmp == LABEL_CHAR)
	{
		if (!(var->com_arg[args] = label(tmp)))
			error(champion, "bad argument");
	}
	else
	{
		champion->expect = tmp;
		if (*tmp == '-')
			tmp++;
		while (ft_isdigit(*tmp))
			tmp++;
		var->com_arg[args] = ft_strsub(champion->expect, 0,
			tmp - champion->expect);
		var->com_arg[args + 1] = NULL;
	}
}

void			check_err_aft(t_com *var,
	t_champ *champion, int args, int i)
{
	int			count;

	count = -1;
	if (var->mass[args] || args < OP(i).nb_arg)
	{
		while (var->mass[++count])
			ft_strdel(&var->mass[count]);
		free(var->mass);
		error(champion, "bad number of arguments");
	}
	while (var->mass[++count])
		ft_strdel(&var->mass[count]);
	free(var->mass);
	if (champion->labelprev)
	{
		lstadd(&var->label, champion->labelprev);
		champion->labelprev = NULL;
	}
	var->n = champion->n;
	lstadd(&champion->token, var);
}

void			parse_com(t_champ *champion, int i)
{
	char		*tmp;
	int			args;
	t_com		*var;

	args = 0;
	var = initvar(champion, i);
	var->mass = checksub(champion, i);
	while (var->mass[args] && args < OP(i).nb_arg)
	{
		tmp = var->mass[args];
		while (*tmp == '\t' || *tmp == ' ')
			tmp++;
		if (*tmp == 'r' && ft_atoi((tmp + 1)) >= 0
			&& ft_atoi((tmp + 1)) <= 99 && OP(i).args[args] & T_REG)
			ifreg(tmp, var, champion, args);
		else if (*tmp == DIRECT_CHAR && OP(i).args[args] & T_DIR)
			ifdir(tmp, var, champion, args);
		else if ((ft_isdigit(*tmp) || *tmp == LABEL_CHAR ||
		(*tmp == '-' && ft_isdigit(*(tmp + 1)) && OP(i).args[args] & T_IND)))
			ifindir(tmp, var, champion, args);
		else
			error(champion, "bad argument");
		args++;
	}
	check_err_aft(var, champion, args, i);
}

int				parse_label(t_champ *champion)
{
	char		*tmp;
	t_com		*tt;

	tmp = champion->expect;
	while (ft_strchr(LABEL_CHARS, *tmp))
		tmp++;
	if (tmp != champion->expect && *tmp == LABEL_CHAR)
	{
		tt = lstnew();
		tt->com_name = ft_strsub(champion->expect, 0, tmp - champion->expect);
		tt->n = champion->n;
		lstadd(&champion->labelprev, tt);
		tmp++;
		while (*tmp == '\t' || *tmp == ' ')
			tmp++;
		if (!*tmp || *tmp == '#' || *tmp == ';')
			return (1);
		champion->expect = tmp;
	}
	return (0);
}

void			dop_noc(t_champ *champion, char **dest, char *tmp, char *tmp2)
{
	char		*line;
	int			end;

	while ((end = get_next_lines(champion->fd, &line)) && ++champion->n)
	{
		if (end == 2)
		{
			ft_strdel(&line);
			ft_strdel(&tmp);
			error(champion, "unexpected end of input");
		}
		if (ft_strchr(line, '"'))
		{
			tmp2 = ft_strsub(line, 0, ft_strchr(line, '"') - line);
			*dest = ft_new_strjoin(tmp, tmp2);
			ft_strdel(&tmp2);
			ft_strdel(&champion->line);
			champion->line = line;
			champion->expect = ft_strchr(line, '"') + 1;
			break ;
		}
		tmp = ft_new_strjoin(tmp, line);
		tmp = ft_new_strjoin(tmp, "\n");
		ft_strdel(&line);
	}
}
