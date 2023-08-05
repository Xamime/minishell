/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:33:58 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/05 17:48:46 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*new_string_heredoc(t_expansion *exp, char *str)
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
		if (str[i] == '$' && !exp->found_dollar && str[i + 1]
			&& (!check_forbidden_char(&str[i + 1], 0) || str[i + 1] == '?'))
			add_var_value(exp, new_str, &i, &j);
		new_str[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	return (new_str);
}

static char	*get_expanded_str(t_expansion *exp, char *tmp, t_expv *expv)
{
	char	*new_str;

	exp->var = ft_getenv(exp->name, expv);
	if (exp->var)
		new_str = new_string_heredoc(exp, tmp);
	else
	{
		exp->var = "";
		new_str = new_string_heredoc(exp, tmp);
	}
	free(tmp);
	free(exp->name);
	return (new_str);
}

static char	*get_exit_code_heredoc(t_expansion *exp, char *tmp)
{
	char	*new_str;

	exp->name = "?";
	exp->var = ft_itoa(g_exit_code);
	new_str = new_string_heredoc(exp, tmp);
	free(tmp);
	free(exp->var);
	return (new_str);
}

char	*get_expanded_str_heredoc(char *str, t_expv *expv)
{
	t_expansion	*exp;
	char		*new_str;
	int			i;

	i = 0;
	new_str = ft_strdup(str);
	exp = malloc(sizeof(t_expansion));
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			new_str = get_exit_code_heredoc(exp, new_str);
		else if (str[i] == '$' && str[i + 1] && !check_forbidden_char(&str[i + 1], 0))
		{
			exp->name = get_var_name(&str[i]);
			new_str = get_expanded_str(exp, new_str, expv);
		}
		i++;
	}
	free(exp);
	return (new_str);
}
