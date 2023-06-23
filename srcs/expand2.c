/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:35:03 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/16 18:47:46 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_and_copy(char *str, char *new_str, char c, int *j)
{
	int	i;

	i = 0;
	new_str[i] = str[i];
	i++;
	while (str[i] && str[i] != c)
	{
		new_str[i] = str[i];
		i++;
	}
	(*j) += i;
	return (i);
}

char	*new_string(t_expansion *exp, char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = set_new_str(exp, str);
	i = 0;
	j = 0;
	exp->found_dollar = 0;
	exp->in_double = 0;
	while (str[i])
	{
		if ((str[i] == '\"' && exp->mode == 0)
			|| (str[i] == '\'' && !exp->in_double))
			i += skip_and_copy(&str[i], &new_str[j], str[i], &j);
		if (str[i] == '\"')
			set_double_quotes(exp);
		if (str[i] == '$' && !exp->found_dollar && check_plus_one(str[i + 1]))
			add_var_value(exp, new_str, &i, &j);
		new_str[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	return (new_str);
}

char	*set_new_str(t_expansion *exp, char *str)
{
	int		var_s;
	int		str_s;
	int		name_s;
	char	*new_str;

	var_s = ft_strlen(exp->var);
	str_s = ft_strlen(str);
	name_s = ft_strlen(exp->name);
	new_str = ft_calloc(sizeof(char), (str_s - (name_s + 1) + var_s + 1));
	return (new_str);
}

void	set_double_quotes(t_expansion *exp)
{
	if (exp->mode == 1 && !exp->in_double)
		exp->in_double = 1;
	else if (exp->mode == 1 && exp->in_double)
		exp->in_double = 0;
}

void	add_var_value(t_expansion *exp, char *new_str, int *i, int *j)
{
	(*i) += ft_strlen(exp->name) + 1;
	ft_strlcat(new_str, exp->var, ft_strlen(exp->var) + (*j) + 1);
	(*j) += ft_strlen(exp->var);
	exp->found_dollar = 1;
}
