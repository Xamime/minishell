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
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		nbr;

	if (n != -2147483648)
	{
		if (n < 0)
		{
			n = -n;
			ft_putchar_fd('-', fd);
		}
		nbr = n % 10;
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(nbr + '0', fd);
	}
	else
		write(fd, "-2147483648", 11);
}
