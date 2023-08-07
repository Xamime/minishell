/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:03:09 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 01:16:01 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_len(char *s, char *charset)
{
	size_t	i;
	char	quote;

	i = 0;
	while (*s && !is_in_set(*s, charset))
	{
		if (*s && is_in_set(*s, "\'\"") && is_paired(s, *s))
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

static char	*word(char *s, char *charset)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_len(s, charset) + 1));
	if (str == NULL)
		return (NULL);
	while (i < ft_len(s, charset))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	nbwords(char *s, char *charset)
{
	int	i;

	i = 0;
	while (*s && is_in_set(*s, charset))
		s++;
	while (*s != '\0')
	{
		i++;
		while (*s && !is_in_set(*s, charset))
		{
			if (is_in_set(*s, "\'\"") && is_paired(s, *s))
				s = skip_to_char(s, *s);
			s++;
		}
		while (*s && is_in_set(*s, charset))
			s++;
	}
	return (i);
}

static void	fill_array(char **str, char *s, char *charset)
{
	int	i;

	i = 0;
	while (*s && is_in_set(*s, charset))
		s++;
	while (*s != '\0')
	{
		str[i] = word(s, charset);
		i++;
		while (*s != '\0' && !is_in_set(*s, charset))
		{
			if (is_in_set(*s, "\'\"") && is_paired(s, *s))
				s = skip_to_char(s, *s);
			s++;
		}
		while (*s && is_in_set(*s, charset))
			s++;
	}
}

char	**ft_split_quotes(char *s, char	*charset)
{
	int		i;
	char	**str;

	if (s == NULL)
		return (NULL);
	i = nbwords(s, charset);
	str = malloc(sizeof(char *) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i] = NULL;
	fill_array(str, s, charset);
	return (str);
}
