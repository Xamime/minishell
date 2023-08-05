/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:47:57 by marvin            #+#    #+#             */
/*   Updated: 2023/08/03 17:47:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_name(char *str)
{
	char	*name;
	int		i;

	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	name = ft_substr(str, 1, i - 1);
	return (name);
}

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
