/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:50:56 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/16 19:09:51 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	if (*to_find == 0)
		return (str);
	while (*str)
	{
		if (*str == *to_find)
		{
			if (ft_strcmp(str, to_find))
				return (str);
		}
		str++;
	}
	return (0);
}
