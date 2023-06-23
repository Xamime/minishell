/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:18:25 by mdesrose          #+#    #+#             */
/*   Updated: 2022/10/01 18:22:48 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putnbr_fd_count(int n, int fd, int *count)
{
	int		nbr;

	if (n != -2147483648)
	{
		if (n < 0)
		{
			n = -n;
			ft_putchar_fd_count('-', fd, count);
		}
		nbr = n % 10;
		if (n > 9)
			ft_putnbr_fd_count(n / 10, fd, count);
		ft_putchar_fd_count(nbr + '0', fd, count);
	}
	else
	{
		write(fd, "-2147483648", 11);
		(*count) += 11;
	}
}
