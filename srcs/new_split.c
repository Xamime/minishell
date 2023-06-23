/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:17:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/04/18 19:13:47 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*int	is_in_set(char c, char *set)
{
	while (*set && *set != c)
		set++;
	if (*set)
		return (1);
	return (0);
}

int	is_paired(char *str, char quote)
{
	str++;
	while (*str && *str != quote)
		str++;
	if (*str)
		return (1);
	return (0);
}

static int	ft_len(char *s, char *set)
{
	size_t	i;

	i = 1;

	while (s[i])
	{
		if (s[i] == ' ' || (is_in_set(s[i], set) && is_paired(&s[i], s[i])))
			break ;
		i++;
	}
	return (i);
}

static char	*word(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_len(s, " \'\"") + 1));
	if (str == NULL)
		return (NULL);
	while (i < ft_len(s, " \'\""))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_len_in_quotes(char *s)
{
	size_t	i;

	i = 1;
	if (!is_in_set(*s, "\'\""))
	{
		printf("Error len_quotes");
		return (-1);
	}
	while (s[i] != s[0])
		i++;
	return (i - 1);
}

char	*word_in_quotes(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_len_in_quotes(s) + 1));
	if (str == NULL)
		return (NULL);
	while (i < ft_len_in_quotes(s))
	{
		str[i] = s[i + 1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*skip_to_char(char *str, char c)
{
	str++;
	while (*str && *str != c)
		str++;
	return (str);
}

int	nbwords(char *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && ft_isprint(*s + 1))
		s++;
	while (*s)
	{
		if (!(is_in_set(*s, "\'\"") && is_paired(s, *s)))
			i++;
		//ft_printf("word : %c, i : %d, len : %d\n\n", *s, i, ft_len(s, " \'\""));
		while ((*s && *s != c))
		{
			if (is_in_set(*s, "\'\"") && is_paired(s, *s))
			{
				s = skip_to_char(s, *s);
				if (*(s + 1) && *(s + 1) != c)
					i += 2;
				else
					i++;
			}
			s++;
		}
		while (*s == c && ft_isprint(*s + 1))
			s++;
	}
	return (i);
}

static void	fill_array(t_token *tokens, char *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && ft_isprint(*s + 1))
		s++;
	while (*s)
	{
		while ((*s && *s != c))
		{
			if (is_in_set(*s, "\'\"") && is_paired(s, *s))
			{
				tokens[i].content = word_in_quotes(s, c);
				tokens[i].quote_type = *s;
				s += ft_strlen(tokens[i].content) + 1;
				i++;
			}
			else
			{
				tokens[i].content = word(s, c);
				tokens[i].quote_type = 0;
				s += ft_strlen(tokens[i].content) - 1;
				i++;
			}
			s++;
		}
		while (*s == c && ft_isprint(*s + 1))
			s++;
	}
}

t_token	*ft_split2(char *s, char c)
{
	int		i;
	t_token	*tokens;

	if (s == NULL)
		return (NULL);
	i = nbwords(s, c);
	//printf("nbwords : %d\n", i);
	tokens = malloc(sizeof(t_token) * (i + 1));
	if (tokens == NULL)
		return (NULL);
	tokens[i].content = NULL;
	fill_array(tokens, s, c);
	return (tokens);
}*/
