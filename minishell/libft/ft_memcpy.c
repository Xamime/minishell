/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:43:22 by mdesrose          #+#    #+#             */
/*   Updated: 2022/09/28 19:44:44 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*str;
	size_t			i;

	i = 0;
	s = (unsigned char *)src;
	str = (unsigned char *)dest;
	if (dest == 0 && src == 0)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	return (dest);
}
