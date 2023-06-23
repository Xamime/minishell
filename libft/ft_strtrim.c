/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:55:16 by mdesrose          #+#    #+#             */
/*   Updated: 2022/10/01 15:52:12 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_trim(char const s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	j = ft_strlen(s1);
	while (ft_trim(s1[i], set))
		i++;
	if (i == j)
	{
		str = ft_calloc(sizeof(char), 1);
		return (str);
	}
	while (ft_trim(s1[j - 1], set))
		j--;
	str = ft_substr(s1, i, j - i);
	return (str);
}
