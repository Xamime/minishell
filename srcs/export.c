/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:15:22 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/27 11:22:40 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	parse_export(t_cmd *cmd, t_expv **expv)
{
	int		i;
	char	*name;
	char	*var;

	i = 1;
	while (cmd->words[i])
	{
		if (!check_forbidden_character(cmd->words[i]))
		{
			set_var_line(cmd->words[i], &name, &var);
			if (!is_in(*expv, name))
				ft_expv_add_back(expv, ft_expv_new(var, name));
			else if (var && ft_strstr(cmd->words[i], "+="))
				change_var(*expv, name, var, 1);
			else if (var)
				change_var(*expv, name, var, 0);
			else
				free(name);
		}
		else
			cmd->status = 1;
		i++;
	}
}

void	export(t_cmd *cmd, t_expv **expv)
{
	parse_export(cmd, expv);
	if (!cmd->words[1])
		export_print(*expv);
}
