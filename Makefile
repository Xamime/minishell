# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:50:28 by mdesrose          #+#    #+#              #
#    Updated: 2023/07/24 03:08:38 by jfarkas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	$(wildcard srcs/*.c)

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
