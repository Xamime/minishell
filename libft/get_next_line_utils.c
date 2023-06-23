/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:09:11 by mdesrose          #+#    #+#             */
/*   Updated: 2023/03/21 17:37:31 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_line(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}
/*
void	ft_bzero(void *s, int n)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}*/

char	*ft_strchr2(const char *s, int c)
{
	int				i;
	unsigned char	uc;

	if (!s)
		return (NULL);
	uc = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == uc)
			return ((char *)s + i + 1);
		i++;
	}
	if (!uc && !s[i])
		return ((char *)s + i);
	return (NULL);
}
/*
static void	*ft_calloc(int nmemb, int size)
{
	void	*ptr;
	int		tot;

	tot = nmemb * size;
	if (nmemb > 2147483647 || size > 2147483647)
	{
		return (NULL);
	}
	if (tot > 2147483647)
	{
		return (NULL);
	}
	ptr = malloc(tot);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, tot);
	return (ptr);
}

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen_line(s, '\0'))
	{
		sub = ft_calloc(1, sizeof(char));
		if (!sub)
			return (NULL);
		return (sub);
	}
	if (len > ft_strlen_line(s, '\0') - start)
		len = ft_strlen_line(s, '\0') - start;
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	return (sub);
}*/
