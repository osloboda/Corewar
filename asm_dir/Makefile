# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osloboda <osloboda@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/04 14:11:49 by osloboda          #+#    #+#              #
#    Updated: 2019/03/21 15:27:07 by osloboda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  ../asm

INCDIR = includes/
 
SRC = main.c op.c incode.c valid.c sub_args.c parse_label.c parse_token.c error.c

SRCDIR = srcs

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

FSRC = $(addprefix $(SRCDIR)/, $(SRC))

LIB = ../libft/ -lft
LIB_H = -I ../libft/

FLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re cleanlib fcleanlib relib

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	@gcc $(FLAGS) $(OBJ) -L $(LIB) -o $(NAME)
	@echo \\033[32mASM Compiled\\033[0m

$(LIB):
	@make -C ../libft all
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h | $(OBJDIR)
	@echo "\033[35mCompiling $<...\033[0m"
	@gcc $(FLAGS) -o $@ -c $< -I $(INCDIR) $(LIB_H)

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@rm -Rf $(OBJDIR)
	@echo \\033[34m======[Cleaned]=========\\033[0m

fclean: clean
	@rm -f $(NAME)

re: fclean all

cleanlib:
	make -C libft clean

fcleanlib:
	make -C libft fclean

relib:
	make -C libft re
