/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:40:48 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/27 16:46:15 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmodf.h"

static double		modf_else(int64_t i0, int32_t j0, double x, double *iptr)
{
	uint64_t	i;
	t_db		iw_u;

	i = UINT64_C(0x000fffffffffffff) >> j0;
	if ((i0 & i) == 0)
	{
		*iptr = x;
		iw_u.word = i0 & UINT64_C(0x8000000000000000);
		x = iw_u.value;
		return (x);
	}
	else
	{
		iw_u.word = (i0 & (~i));
		(*iptr) = iw_u.value;
		return (x - *iptr);
	}
}

double				ft_modf(double x, double *iptr)
{
	int32_t		j0;
	t_db		iw_u;
	t_db		gh_u;

	gh_u.value = x;
	j0 = ((gh_u.word >> 52) & 0x7ff) - 0x3ff;
	if (j0 < 52)
	{
		if (j0 < 0)
		{
			iw_u.word = gh_u.word & UINT64_C(0x8000000000000000);
			*iptr = iw_u.value;
			return (x);
		}
		else
			return (modf_else(gh_u.word, j0, x, iptr));
	}
	*iptr = x;
	if (j0 == 0x400 && (gh_u.word & UINT64_C(0xfffffffffffff)))
		return (x);
	iw_u.word = (gh_u.word & 0x8000000000000000);
	(x) = iw_u.value;
	return (x);
}

static void			ft_set(long double *iptr, int exp,
		uint32_t msw, uint32_t lsw)
{
	t_ld	new;

	new.parts.sign_exponent = exp;
	new.parts.lsw = lsw;
	new.parts.msw = msw;
	(*iptr) = new.value;
}

static long double	ft_modfl_else2(int32_t j0,
	t_ld ew_u, long double x, long double *iptr)
{
	uint32_t	i;

	*iptr = x;
	i = ((uint32_t)(0x7fffffff)) >> (j0 - 32);
	if (j0 > 63)
	{
		if (j0 == 0x4000 && ((ew_u.parts.msw & 0x7fffffff) | ew_u.parts.lsw))
			return (x);
		ft_set(&x, ew_u.parts.sign_exponent & 0x8000, 0, 0);
		return (x);
	}
	else
	{
		if ((ew_u.parts.lsw & i) == 0)
		{
			ft_set(&x, ew_u.parts.sign_exponent & 0x8000, 0, 0);
			return (x);
		}
		ft_set(iptr, ew_u.parts.sign_exponent, ew_u.parts.msw,
			ew_u.parts.lsw & (~i));
		return (x - *iptr);
	}
}

long double			ft_modfl(long double x, long double *iptr)
{
	int32_t		j0;
	uint32_t	i;
	t_ld		ew_u;

	ew_u.value = x;
	j0 = (ew_u.parts.sign_exponent & 0x7fff) - 0x3fff;
	i = (0x7fffffff) >> j0;
	if (j0 < 32)
	{
		if (j0 < 0)
		{
			ft_set(iptr, ew_u.parts.sign_exponent & 0x8000, 0, 0);
			return (x);
		}
		if (((ew_u.parts.msw & i) | ew_u.parts.lsw) == 0)
		{
			*iptr = x;
			ft_set(&x, ew_u.parts.sign_exponent & 0x8000, 0, 0);
			return (x);
		}
		ft_set(iptr, ew_u.parts.sign_exponent, ew_u.parts.msw & (~i), 0);
		return (x - *iptr);
	}
	return (ft_modfl_else2(j0, ew_u, x, iptr));
}
