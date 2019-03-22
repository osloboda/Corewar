/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmodf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:10:58 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/26 19:12:26 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMODF_H
# define LIBMODF_H

# include <stdint.h>

typedef union
{
	double			value;
	struct
	{
		uint32_t	lsw;
		uint32_t	msw;
	}				parts;
	uint64_t		word;
}					t_db;

typedef union
{
	long double			value;
	struct
	{
		uint32_t		lsw;
		uint32_t		msw;
		int				sign_exponent:16;
		unsigned int	empty1:16;
		unsigned int	empty0:32;
	}					parts;
}						t_ld;

double					ft_modf(double x, double *iptr);
long double				ft_modfl(long double x, long double *iptr);

#endif
