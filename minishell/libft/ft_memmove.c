/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:51:45 by mdesrose          #+#    #+#             */
/*   Updated: 2022/10/01 17:15:45 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*str;

	s = (unsigned char *)src;
	str = (unsigned char *)dest;
	if (dest == 0 && src == 0)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	while (n > 0)
	{
		str[n - 1] = s[n - 1];
		n--;
	}
	return (dest);
}
