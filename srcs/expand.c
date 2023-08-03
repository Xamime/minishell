/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:44:19 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/03 17:50:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_expanded_str(t_expansion *exp, char *tmp, t_expv *expv)
{
	char	*new_str;

	exp->var = ft_getenv(exp->name, expv);
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

char	*str_exit_code(char *str, t_expv *expv, t_expansion *exp)
{
	char	*new_str;
	char	*exit_code;

	exit_code = ft_itoa(g_exit_code);
	new_str = malloc(sizeof(char) * ft_strlen(str) + ft_strlen(exit_code));
	exp->found_dollar = 0;
	exp->in_double = 0;
	new_str = new_str_exit(str, new_str, exit_code, exp);
	return (new_str);
}

static char	*get_expanded_str2(t_expansion *exp, char *tmp)
{
	char	*new_str;

	exp->name = "?";
	exp->var = ft_itoa(g_exit_code);
	new_str = new_string(exp, tmp);
	free(tmp);
	free(exp->var);
	return (new_str);
}

static char	*expand_var(char *str, t_expansion *exp, t_expv *expv, int mode)
{
	char		*new_str;
	int			in_double;

	in_double = 0;
	new_str = ft_strdup(str);
	while (str && *str)
	{
		if ((*str == '"' && exp->mode == 0) || (*str == '\'' && !in_double))
			str = skip_to_char(str, *str);
		if (*str == '\"' && mode == 1 && !in_double)
			in_double = 1;
		else if (*str == '\"' && mode == 1 && in_double)
			in_double = 0;
		if (*str == '$' && *(str + 1) == '?')
			new_str = get_expanded_str2(exp, new_str);
		else if (*str == '$' && *(str + 1) && !check_forbidden_char(str + 1, 0))
		{
			exp->name = get_var_name(str);
			new_str = get_expanded_str(exp, new_str, expv);
		}
		str++;
	}
	return (new_str);
}

char	*make_dollars(char *str, t_expv *expv, int mode)
{
	t_expansion	*exp;
	char		*new_str;
	
	exp = malloc(sizeof(t_expansion));
	exp->mode = mode;
	new_str = expand_var(str, exp, expv, mode);
	free(exp);
	return (new_str);
}
