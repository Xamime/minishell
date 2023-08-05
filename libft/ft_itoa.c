/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:54:47 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/05 14:57:46 by jfarkas          ###   ########.fr       */
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

#include <limits.h>
#include "libft.h"

char	*ft_lltoa(long long n)
{
	char		*str;
	long long	i;

	if (n == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
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
	return (str);
}
