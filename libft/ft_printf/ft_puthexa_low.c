/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_low.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:34:26 by mdesrose          #+#    #+#             */
/*   Updated: 2022/10/05 19:01:21 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_puthexa_low(unsigned int nb, int *count)
{
	unsigned int		nbr;
	char				*str;

	str = "0123456789abcdef";
	nbr = nb % 16;
	if (nb > 15)
		ft_puthexa_low(nb / 16, count);
	ft_putchar_fd_count(str[nbr], 1, count);
}
