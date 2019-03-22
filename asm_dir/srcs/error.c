/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:24:07 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/22 12:57:31 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_com			*lstnew(void)
{
	t_com		*t;

	if (!(t = (t_com*)malloc(sizeof(t_com))))
		return (NULL);
	t->next = NULL;
	t->prev = NULL;
	t->com_name = NULL;
	t->label = NULL;
	return (t);
}

void			lstadd(t_com **alst, t_com *new)
{
	t_com		*t;

	if (alst != NULL && new != NULL)
	{
		t = *alst;
		if (t)
		{
			while (t->next)
				t = t->next;
			t->next = new;
			new->prev = t;
		}
		else
			*alst = new;
	}
}

void			dop_error(t_champ *champion)
{
	if (champion->labelprev && champion->labelprev->com_name)
	{
		ft_strdel(&champion->labelprev->com_name);
		free(champion->labelprev);
	}
	ft_strdel(&champion->comment);
	ft_strdel(&champion->name);
	ft_strdel(&champion->line);
	ft_strdel(&champion->out);
	free(champion);
	exit(0);
}

void			error(t_champ *champion, char *error)
{
	t_com		*tmp;
	t_com		*tt;
	char		*er;

	ft_printf("Line %i: Syntax error - %s\n", champion->n,
		(er = ft_strdup(error))) ? ft_strdel(&er) : 0;
	while (champion->token)
	{
		tmp = champion->token->next;
		while (champion->token->label)
		{
			tt = champion->token->label->next;
			ft_strdel(&champion->token->label->com_name);
			free(champion->token->label);
			champion->token->label = tt;
		}
		ft_strdel(&champion->token->com_name);
		ft_strdel(&champion->token->com_arg[0]);
		ft_strdel(&champion->token->com_arg[1]);
		ft_strdel(&champion->token->com_arg[2]);
		free(champion->token->com_arg);
		free(champion->token);
		champion->token = tmp;
	}
	dop_error(champion);
}

int				checkformat(char *name)
{
	char		*tmp;

	tmp = name;
	while (*tmp == '.' || *tmp == '/')
		tmp++;
	tmp = ft_strchr(tmp, '.');
	while (ft_strchr(tmp + 1, '.'))
		tmp = ft_strchr(tmp + 1, '.');
	if (tmp && *(tmp + 1) == 's' &&
		*(tmp + 2) == '\0' && *(tmp - 1))
		return (1);
	return (0);
}
