/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:54:47 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/01 00:29:05 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_size(long long nb)
{
	long long	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	long long	i;
	long long	nbr;

	nbr = n;
	i = ft_size(nbr);
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	str[i] = '\0';
	while (nbr > 0)
	{
		str[i - 1] = 48 + (nbr % 10);
		nbr = nbr / 10;
		i--;
	}
	return (str);
}

char	*ft_lltoa(long long n)
{
	char		*str;
	long long	i;

	i = ft_size(n);
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[i] = '\0';
	while (n > 0)
	{
		str[i - 1] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	// if (n == -9223372036854775808)
	// 	str = "-9223372036854775808";
	return (str);
}