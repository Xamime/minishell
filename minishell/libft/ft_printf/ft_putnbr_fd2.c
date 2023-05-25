/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:01:33 by mdesrose          #+#    #+#             */
/*   Updated: 2022/10/05 23:30:56 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putnbr_fd2(unsigned int n, int fd, int *count)
{
	unsigned int	nbr;

	nbr = n % 10;
	if (n > 9)
		ft_putnbr_fd_count(n / 10, fd, count);
	ft_putchar_fd_count(nbr + '0', fd, count);
}
