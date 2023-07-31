# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:50:28 by mdesrose          #+#    #+#              #
#    Updated: 2023/08/01 00:05:33 by mdesrose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	srcs/builtins/builtins_utils.c \
		srcs/builtins/cd.c \
		srcs/builtins/echo.c \
		srcs/builtins/export_utils.c \
		srcs/builtins/export_utils2.c \
		srcs/builtins/export.c \
		srcs/builtins/pwd.c \
		srcs/builtins/unset.c \
		srcs/builtins/exit.c \
		srcs/utils/utils1.c \
		srcs/utils/utils2.c \
		srcs/utils/free_utils.c \
		srcs/exec/exec.c \
		srcs/exec/exec_utils.c \
		srcs/expand.c \
		srcs/expand2.c \
		srcs/export_list_utils.c \
		srcs/init.c \
		srcs/main.c \
		srcs/parsing.c \
		srcs/parsing2.c \
		srcs/access.c \
		srcs/redirs.c \
		srcs/redirs_utils.c \
		srcs/split_quotes_utils.c \
		srcs/split_quotes.c \
		srcs/syntax_check.c

NAME = minishell
LIBFT_SRC = libft
LIBFT = ${LIBFT_SRC}/libft.a
CC = clang
CFLAGS = -g #-lreadline #-Wall -Wextra -Werror -g
OBJ = $(SRC:c=o)

YELLOW=\033[0;33m
GREEN=\033[0;32m
RED=\033[0;31m
DEFAULT=\033[39m
CLEANL=\r\033[K

all: $(NAME)

%.o: %.c
	@echo -n "$(CLEANL)$(YELLOW)Generating $(NAME) objects... $@$(DEFAULT)"
	@${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(CLEANL)$(GREEN)Done generating $(NAME) objects !$(DEFAULT)"
	@echo -n "$(GREEN)Compiling $(NAME)...$(DEFAULT)"
	@$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME) $(LIBFT)
	@echo "$(CLEANL)$(GREEN)Done compiling $(NAME) !$(DEFAULT)"

${LIBFT}:
	@make all -C ${LIBFT_SRC} -s

clean:
	@echo "$(RED)Deleting $(NAME) objects...$(DEFAULT)"
	@rm -f $(OBJ)
	@make clean -C ${LIBFT_SRC} -s

fclean: clean
	@echo "$(RED)Deleting $(NAME) executable...$(DEFAULT)"
	@rm -f $(NAME)
	@make fclean -C ${LIBFT_SRC} -s

re: fclean all

.PHONY: clean fclean re
