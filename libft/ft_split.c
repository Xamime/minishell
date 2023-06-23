/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:45:24 by mdesrose          #+#    #+#             */
/*   Updated: 2023/03/28 18:38:17 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*word(char const *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_len(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (i < ft_len(s, c))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	nbwords(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && ft_isprint(*s + 1))
		s++;
	while (*s != '\0')
	{
		i++;
		while (*s != '\0' && *s != c)
			s++;
		while (*s == c && ft_isprint(*s + 1))
			s++;
	}
	return (i);
}

static void	fill_array(char **str, char const *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && ft_isprint(*s + 1))
		s++;
	while (*s != '\0')
	{
		str[i] = word(s, c);
		i++;
		while (*s != '\0' && *s != c)
			s++;
		while (*s == c && ft_isprint(*s + 1))
			s++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**str;

	if (s == NULL)
		return (NULL);
	i = nbwords(s, c);
	str = malloc(sizeof(char *) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i] = NULL;
	fill_array(str, s, c);
	return (str);
}
