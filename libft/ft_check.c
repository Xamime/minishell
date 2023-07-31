/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:36:37 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/31 19:08:36 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check(int fd, char c, va_list *args, int *count)
{
	if (c == 'c')
		ft_putchar_fd_count(va_arg(*args, int), fd, count);
	else if (c == 's')
		ft_putstr_fd_count(va_arg(*args, char *), fd, count);
	else if (c == 'p')
		ft_puthexa_p_low(va_arg(*args, void *), count);
	else if (c == 'd')
		ft_putnbr_fd_count(va_arg(*args, int), fd, count);
	else if (c == 'i')
		ft_putnbr_fd_count(va_arg(*args, int), fd, count);
	else if (c == 'u')
		ft_putnbr_fd2(va_arg(*args, unsigned int), fd, count);
	else if (c == 'x')
		ft_puthexa_low(va_arg(*args, unsigned int), count);
	else if (c == 'X')
		ft_puthexa_up(va_arg(*args, unsigned int), count);
	else if (c == '%')
		ft_putchar_fd_count('%', fd, count);
}
