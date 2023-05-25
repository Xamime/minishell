/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_up.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:36:05 by mdesrose          #+#    #+#             */
/*   Updated: 2022/10/05 16:36:13 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_puthexa_up(unsigned int nb, int *count)
{
	int		nbr;
	char	*str;

	str = "0123456789ABCDEF";
	nbr = nb % 16;
	if (nb > 15)
		ft_puthexa_up(nb / 16, count);
	ft_putchar_fd_count(str[nbr], 1, count);
}
