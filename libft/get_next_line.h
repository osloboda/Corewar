/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:16:55 by ahavrius          #+#    #+#             */
/*   Updated: 2018/11/04 18:33:38 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE 2

int				get_next_line(const int fd, char **line);
int				get_next_lines(const int fd, char **line);

typedef struct	s_buff
{
	int		isspace;
	char	*str;
	int		fd;
}				t_buff;

#endif
