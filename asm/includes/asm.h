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

# ifndef ASM_H
#define ASM_H

#include "../libft/libft.h"

typedef struct		s_champ
{
	char			*name;
	char 			*comment;
	size_t			content_size;
	struct s_list	*next;
}					t_champ;

#endif
