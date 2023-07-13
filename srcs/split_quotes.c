/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:03:09 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/13 22:38:03 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_len(char *s, char *set)
{
	size_t	i;
	char	quote;

	i = 0;
	while (*s && *s != ' ')
	{
		if (is_in_set(*s, set) && is_paired(s, *s))
		{
			quote = *s;
			s++;
			i++;
			while (*s && *s != quote)
			{
				s++;
				i++;
			}
		}
		i++;
		s++;
	}
	return (i);
}

static char	*word(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_len(s, "\'\"") + 1));
	if (str == NULL)
		return (NULL);
	while (i < ft_len(s, "\'\""))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	nbwords(char *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && ft_isprint(*s + 1))
		s++;
	while (*s != '\0')
	{
		i++;
		while (*s && *s != c)
		{
			if (is_in_set(*s, "\'\"") && is_paired(s, *s))
				s = skip_to_char(s, *s);
			s++;
		}
		while (*s == c && ft_isprint(*s + 1))
			s++;
	}
	return (i);
}

static void	fill_array(char **str, char *s, char c)
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
		{
			if (is_in_set(*s, "\'\"") && is_paired(s, *s))
				s = skip_to_char(s, *s);
			s++;
		}
		while (*s == c && ft_isprint(*s + 1))
			s++;
	}
}

char	**ft_split_quotes(char *s, char c)
{
	int		i;
	char	**str;

	// faut split sur " \t\n"
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
