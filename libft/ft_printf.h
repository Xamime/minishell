/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:38:07 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/31 19:18:39 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

void		ft_putnbr_fd2(unsigned int n, int fd, int *count);
void		ft_putnbr_fd_count(int n, int fd, int *count);
void		ft_putstr_fd_count(char *s, int fd, int *count);
void		ft_putchar_fd_count(char c, int fd, int *count);
void		ft_check(int fd, char c, va_list *args, int *count);
int			printf_fd(int fd, const char *str, ...);
void		ft_puthexa_low(unsigned int nb, int *count);
void		ft_puthexa_p_low(void *ptr, int *count);
void		ft_puthexa_up(unsigned int nb, int *count);

#endif
