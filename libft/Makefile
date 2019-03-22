NAME = libft.a

CC = clang
FLAGS = -Wall -Wextra -Werror
PRINTF = libftprintf.a

SRC_DIR := ./libft/
OBJ_DIR := ./obj/

SRC := ft_memmove.c ft_strlcat.c ft_memset.c ft_strlen.c ft_atoi.c	ft_new_strjoin.c ft_power_pos.c ft_strmap.c ft_bzero.c ft_putchar.c ft_strmapi.c ft_count_dig.c ft_putchar_fd.c ft_strncat.c ft_isalnum.c ft_putendl.c ft_strncmp.c ft_isalpha.c ft_putendl_fd.c ft_strncpy.c ft_isascii.c ft_putnbr.c ft_strnequ.c ft_isdigit.c ft_putnbr_fd.c ft_strnew.c ft_isprint.c ft_putstr.c ft_strnshift.c ft_itoa.c ft_putstr_fd.c ft_strnstr.c ft_lstadd.c ft_strcat.c ft_strrchr.c ft_lstdel.c ft_strchr.c ft_strshift.c ft_lstdelone.c ft_strclr.c ft_strshiftnot.c ft_lstiter.c ft_strcmp.c ft_strsplit.c ft_lstmap.c ft_strcpy.c ft_strstr.c ft_lstnew.c ft_strdel.c ft_strsub.c ft_memalloc.c ft_strdup.c ft_strtrim.c ft_memccpy.c ft_strequ.c ft_tolower.c ft_memchr.c ft_strinset.c ft_toupper.c ft_memcmp.c ft_striter.c ft_memcpy.c ft_striteri.c ft_memdel.c ft_strjoin.c ft_lst_reverse.c get_next_line.c get_next_lines.c ft_lstlen.c ft_lstdelnext.c ft_lstiter2.c linlist_del_el.c linlist_del_head.c linlist_del_tail.c linlist_delall.c linlist_is_emply.c linlist_iter.c linlist_new_el.c linlist_new_link.c linlist_push_head.c linlist_push_tail.c ft_lstnew_link.c ft_strcountchr.c ft_splitdel.c linlist_find.c ft_lstfind.c linlist_pop_head.c linlist_pop_tail.c linlist_len.c linlist_reverse.c ft_lstsort.c ft_lstmap_link.c ft_lstcopy.c added.c check_mask.c double_added.c format_str.c ft_comf.c ft_printf.c fun_double.c fun_num.c fun_str.c num_added.c ft_atoi_base.c ft_striter_bool.c

OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

.PHONY: all

all:		$(NAME)
	@:

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[31mLibrary compiled!\033[0m"

$(OBJ):		| $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "\033[32mCompiling library...\033[0m"

$(OBJ_DIR)%.o: %.c *.h
	@$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
fclean: clean
	@rm -f $(NAME)
clean_all: clean
	@rm -f *~
re: fclean all

vpath %.c $(SRC_DIR)