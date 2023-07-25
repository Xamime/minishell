/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:44:46 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/25 17:26:09 by jfarkas          ###   ########.fr       */
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

t_expv	*find_min_ascii(t_expv *export, t_expv *sorted)
{
	t_expv	*ptr;
	t_expv	*min;

	ptr = export;
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
			*var = "";
	}
	else
	{
		*name = ft_strdup(line);
		*var = NULL;
	}
}

void	change_var(t_data **data, char *name, char *var, int mode)
{
	t_expv	*tmp;
	char	*to_free;

	tmp = (*data)->export;
	while (tmp && ft_strncmp(tmp->name, name, ft_strlen(name)))
		tmp = tmp->next;
	if (tmp && mode == 0)
		tmp->var = var;
	else if (tmp && mode == 1)
	{
		if (!var[0])
		{
			tmp->var = "";
			return ;
		}
		to_free = tmp->var;
		tmp->var = ft_strjoin(tmp->var, var);
		if (to_free && to_free[0])
			free(to_free);
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
