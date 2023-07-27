/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:44:46 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/27 11:19:44 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export_var(char *name, char *var)
{
	if (var)
		ft_printf("declare -x %s=%c%s%c\n", name, '"', var, '"');
	else
		ft_printf("declare -x %s\n", name);
}

t_expv	*find_min_ascii(t_expv *expv, t_expv *sorted)
{
	t_expv	*ptr;
	t_expv	*min;

	ptr = expv;
	while (is_in(sorted, ptr->name))
		ptr = ptr->next;
	min = ptr;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, min->name, ft_strlen(min->name)) < 0
			&& !is_in(sorted, ptr->name))
			min = ptr;
		ptr = ptr->next;
	}
	return (min);
}

void	set_var_line(char *line, char **name, char **var)
{
	int	equal_index;
	int	var_size;

	equal_index = ft_strchrlen(line, '=');
	if (equal_index != -1)
	{
		var_size = ft_strlen(ft_strchr(line, '=') + 1);
		if (line[equal_index - 1] != '+')
			*name = ft_substr(line, 0, equal_index);
		else
			*name = ft_substr(line, 0, equal_index - 1);
		if (line[equal_index + 1])
			*var = ft_substr(line, equal_index + 1, var_size);
		else
			*var = ft_strdup("");
	}
	else
	{
		*name = ft_strdup(line);
		*var = NULL;
	}
}

void	change_var(t_expv *expv, char *name, char *var, int mode)
{
	t_expv	*tmp;
	char	*to_free;

	tmp = expv;
	while (tmp && ft_strncmp(tmp->name, name, ft_strlen(name)))
		tmp = tmp->next;
	printf("name : %s, var : %s, mode : %d\n", name, var, mode);
	if (tmp && mode == 0)
	{
		if (tmp->var)
			free(tmp->var);
		tmp->var = var;
		free(name);
	}
	else if (tmp && mode == 1)
	{
		to_free = tmp->var;
		tmp->var = ft_strjoin(tmp->var, var);
		if (to_free && to_free[0])
			free(to_free);
		if (var)
			free(var);
		free(name);
	}
}

int	check_forbidden_character(char *str)
{
	int	i;

	if (str[0] != '_' && !ft_isalpha(str[0]))
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", str);
		return (1);
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] == '+' && str[i + 1] == '=')
			&& str[i] != '_' && !ft_isalnum(str[i]))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}
