/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:14:13 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 14:14:14 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_ERROR_H
# define VM_ERROR_H

# define ERROR_NOFILE "ERROR : nothing to open"
# define ERROR_OPENFILE "ERROR : can't open file to read"
# define ERROR_READFILE "ERROR : invalid reading format"
# define ERROR_MAGICNUMBER "ERROR : magic numbers mismatch"
# define ERROR_NULLFORMAT "ERROR : didn't find a NULL"
# define ERROR_PLAYERNUMBER "ERROR : wrong number of a player"
# define ERROR_DOUBLEPLAYERS "ERROR : doublication of players' numbers"
# define ERROR_MEMALLOC "ERROR : can't allocate memory"
# define ERROR_FLAGFORMAT "ERROR : wrong flag format"
# define ERROR_FILECOR "ERROR : invalid file extension"
# define ERROR_TOOLONG "ERROR : file is too long"
# define ERROR_CODESIZE "ERROR : file has too large a code"
# define ERROR_NUMPLAYERS "ERROR : Too many champions"

void	drop_error(char *text_error);

#endif
