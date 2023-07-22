# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:50:28 by mdesrose          #+#    #+#              #
#    Updated: 2023/07/22 15:42:52 by jfarkas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	$(wildcard srcs/*.c)


NAME = minishell
LIBFT_SRC = libft
LIBFT = ${LIBFT_SRC}/libft.a
CC = clang
CFLAGS =  -g -lreadline #-Wall -Wextra -Werror -g
OBJ = $(SRC:c=o)

all: $(NAME)

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-10.10s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@echo "\033[0;32m\nCompiling minishell..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)
	@echo "\033[0mDone !"

${LIBFT}:
	make -C ${LIBFT_SRC} all

clean:
	@echo "\033[0;31mDeleting objects..."
	@rm -f $(OBJ)
	@make clean -C ${LIBFT_SRC}
	@echo "\033[0m"

fclean: clean
	@echo "Deleting executable..."
	@rm -f $(NAME)
	@make fclean -C ${LIBFT_SRC}
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re
