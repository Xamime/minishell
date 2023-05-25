/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_p_low.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:35:33 by mdesrose          #+#    #+#             */
/*   Updated: 2022/10/05 16:35:56 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	put_hexa(unsigned long nb, int *count)
{
	char			*str;
	unsigned long	nbr;

	str = "0123456789abcdef";
	nbr = nb % 16;
	if (nb > 15)
		put_hexa((nb / 16), count);
	ft_putchar_fd_count(str[nbr], 1, count);
}

void	ft_puthexa_p_low(void *ptr, int *count)
{
	unsigned long	nb;

	nb = (unsigned long)ptr;
	if (nb == 0)
	{
		*count += write(1, "(nil)", 5);
		return ;
	}
	*count += write(1, "0x", 2);
	put_hexa(nb, count);
}
