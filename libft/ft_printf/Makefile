# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 09:28:12 by mmarks            #+#    #+#              #
#    Updated: 2022/11/29 16:25:28 by mdesrose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_check.c \
		ft_printf.c \
		ft_puthexa_low.c \
		ft_puthexa_p_low.c \
		ft_puthexa_up.c \
		ft_putstr_fd_count.c \
		ft_putchar_fd_count.c \
		ft_putnbr_fd_count.c \
		ft_putnbr_fd2.c

OBJS = ${SRC:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

CC = clang

AR = ar

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

NAME = libftprintf.a

all : ${NAME}

${NAME}: ${OBJS}
		${AR} rcs $@ $^

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re
