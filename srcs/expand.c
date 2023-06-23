/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:44:19 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/17 19:08:53 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"	

static char	*get_expanded_str(t_expansion *exp, char *tmp, t_data *data)
{
	char	*new_str;

	exp->var = ft_getenv(exp->name, data);
	if (exp->var)
		new_str = new_string(exp, tmp);
	else
	{
		exp->var = "";
		new_str = new_string(exp, tmp);
	}
	free(tmp);
	free(exp->name);
	return (new_str);
}

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

void	remove_quotes(char *str, char *new_str, char quote)
{
	char	*tmp;

	tmp = str;
	while (*str)
	{
		if (is_in_set(*str, "\"\'"))
		{
			quote = *str;
			str++;
			while (str && *str != quote)
			{
				*new_str = *str;
				str++;
				new_str++;
			}
			if (str)
				str++;
		}
		if (str && !is_in_set(*str, "\"\'"))
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
	while (*tmp)
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
	// aled il faut de la place
	remove_quotes(str, new_str, quote);
	return (new_str);
}

char	*make_dollars(char *str, t_data *data, int mode)
{
	char		*new_str;
	t_expansion	*exp;
	int			in_double;

	in_double = 0;
	exp = malloc(sizeof(t_expansion));
	new_str = ft_strdup(str);
	exp->mode = mode;
	while (str && *str)
	{
		if ((*str == '"' && exp->mode == 0) || (*str == '\'' && !in_double))
			str = skip_to_char(str, *str);
		if (*str == '\"' && mode == 1 && !in_double)
			in_double = 1;
		else if (*str == '\"' && mode == 1 && in_double)
			in_double = 0;
		if (*str == '$' && check_plus_one(*(str + 1)))
		{
			exp->name = get_var_name(str);
			new_str = get_expanded_str(exp, new_str, data);
		}
		str++;
	}
	free(exp);
	return (new_str);
}
