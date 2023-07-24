# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 09:28:12 by mmarks            #+#    #+#              #
#    Updated: 2023/07/24 03:09:25 by jfarkas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =   ft_isalpha.c \
		ft_strstr.c \
        ft_isalnum.c \
        ft_isascii.c \
        ft_isprint.c \
        ft_isdigit.c \
        ft_bzero.c \
        ft_memset.c \
        ft_memcpy.c \
        ft_memmove.c \
        ft_memchr.c \
        ft_memcmp.c \
        ft_toupper.c \
        ft_tolower.c \
        ft_strlcpy.c \
        ft_strlcat.c \
        ft_strdup.c \
        ft_strlen.c \
        ft_strrchr.c \
        ft_strchr.c \
        ft_strncmp.c \
        ft_strjoin.c \
        ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_substr.c \
		ft_strtrim.c \
		ft_split.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_itoa.c \
		ft_putstr_fd.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_check.c \
		ft_printf.c \
		ft_puthexa_low.c \
		ft_puthexa_p_low.c \
		ft_puthexa_up.c \
		ft_putstr_fd_count.c \
		ft_putchar_fd_count.c \
		ft_putnbr_fd_count.c \
		ft_putnbr_fd2.c \
		ft_strcmp.c

OBJS =    ${SRC:.c=.o}
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
NAME = libft.a

YELLOW=\033[0;33m
GREEN=\033[0;32m
RED=\033[0;31m
DEFAULT=\033[39m
CLEANL=\r\033[K

%.o : %.c
		@echo -n "$(CLEANL)$(YELLOW)Generating libft objects... $@$(DEFAULT)"
		@$(CC) ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
		@echo "$(CLEANL)$(GREEN)Done generating libft objects !$(DEFAULT)"
		@echo -n "$(GREEN)Compiling libft...$(DEFAULT)"
		@ar rcs $@ $^
		@echo "$(CLEANL)$(GREEN)Done compiling libft !$(DEFAULT)"

all : ${NAME}

clean:
		@echo "$(RED)Deleting libft objects...$(DEFAULT)"
		@${RM} ${OBJS}

fclean: clean
		@echo "$(RED)Deleting libft executable...$(DEFAULT)"
		@${RM} ${NAME}

re : fclean all

.PHONY :  all clean fclean re
