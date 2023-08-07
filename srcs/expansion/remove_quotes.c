/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:59:49 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/07 00:59:49 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	remove_quotes(char *str, char *new_str, char quote, char *tmp)
{
	tmp = str;
	while (str && *str)
	{
		if (is_in_set(*str, "\"\'"))
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
			{
				*new_str = *str;
				str++;
				new_str++;
			}
			if (*str)
				str++;
		}
		if (*str && !is_in_set(*str, "\"\'"))
		{
			*new_str = *str;
			str++;
			new_str++;
		}
	}
	new_str = tmp;
}

char	*set_without_quotes(char *str)
{
	char	*tmp;
	int		size;
	char	*new_str;
	char	quote;

	size = ft_strlen(str);
	tmp = str;
	while (tmp && *tmp)
	{
		if (is_in_set(*tmp, "\"\'"))
		{
			quote = *tmp;
			tmp++;
			size -= 2;
			while (*tmp != quote)
				tmp++;
		}
		tmp++;
	}
	new_str = ft_calloc(size + 1, sizeof(char));
	remove_quotes(str, new_str, quote, tmp);
	return (new_str);
}
