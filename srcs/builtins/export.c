/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:15:22 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/27 15:23:22 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_sorted(t_expv *sorted)
{
	t_expv *tmp;

	while (sorted)
	{
		tmp = sorted;
		sorted = sorted->next;
		free(tmp);
	}
}

static void	export_print(t_expv *expv)
{
	t_expv	*sorted;
	t_expv	*ptr;
	t_expv	*min;
	int		expv_size;
	int		i;

	i = 0;
	expv_size = ft_expv_size(expv);
	sorted = NULL;
	while (i < expv_size)
	{
		min = find_min_ascii(expv, sorted);
		ft_expv_add_back(&sorted, ft_expv_new(min->var, min->name));
		print_export_var(min->name, min->var);
		i++;
	}
	free_sorted(sorted);
}

static void	parse_export(char *str, t_cmd *cmd, t_expv **expv)
{
	char	*name;
	char	*var;

	if (!check_forbidden_character(str, 1))
	{
		set_var_line(str, &name, &var);
		if (!is_in(*expv, name))
			ft_expv_add_back(expv, ft_expv_new(var, name));
		else if (var && ft_strstr(str, "+="))
			change_var(*expv, name, var, 1);
		else if (var)
			change_var(*expv, name, var, 0);
		else
			free(name);
	}
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		cmd->status = 1;
	}
}

void	export(t_cmd *cmd, t_expv **expv)
{
	int	i;

	i = 1;
	if (!cmd->words[1])
		export_print(*expv);
	else
	{
		while (cmd->words[i])
		{
			parse_export(cmd->words[i], cmd, expv);
			i++;
		}
	}
}
