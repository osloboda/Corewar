/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 18:59:32 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/14 20:03:53 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>

# define OP(index) g_op_tab[index]

typedef struct		s_com
{
	char			*com_name;
	char			**com_arg;
	char			**mass;
	struct s_com	*label;
	int				n;
	size_t			com_size;
	struct s_com	*next;
	struct s_com	*prev;
}					t_com;

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	char			*line;
	char			*expect;
	t_com			*labelprev;
	int				n;
	int				fd;
	char			*out;
	size_t			content_size;
	t_com			*token;
}					t_champ;

int					search_label(t_com *com, char *str, t_champ *champ);
void				insize_com(t_champ *champion);
void				incode(t_champ *champion);
void				parse_token(t_champ *champion, int i);
void				error(t_champ *champion, char *error);
int					checkformat(char *name);
t_com				*lstnew(void);
void				lstadd(t_com **alst, t_com *new);
unsigned int		to_big_endian(unsigned int x);
char				*label(char *line);
char				**checksub(t_champ *champion, int i);
t_com				*initvar(t_champ *champion, int i);
int					parse_label(t_champ *champion);
void				parse_com(t_champ *champion, int i);
void				ifreg(char *tmp, t_com *var, t_champ *champion, int args);
void				ifdir(char *tmp, t_com *var, t_champ *champion, int args);
void				get_a(t_com *com, int *karet, unsigned char **inst);
void				dop_noc(t_champ *champion, char **dest,
		char *tmp, char *tmp2);
int					dop_incode(unsigned char **inst,
		t_champ *champion, int *fd, int karet);

#endif
