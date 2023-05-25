/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:15:22 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/16 19:03:25 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_print(t_expv *export)
{
	t_expv	*sorted;
	t_expv	*ptr;
	t_expv	*min;
	int		expv_size;
	int		i;

	i = 0;
	expv_size = ft_expv_size(export);
	sorted = NULL;
	while (i < expv_size)
	{
		min = find_min_ascii(export, sorted);
		ft_expv_add_back(&sorted, ft_expv_new(min->var, min->name));
		print_export_var(min->name, min->var);
		i++;
	}
}

static void	parse_export(t_cmd cmd, t_data *data)
{
	int		i;
	char	*name;
	char	*var;

	i = 1;
	while (cmd.words[i])
	{
		if (!check_forbidden_caracter(cmd.words[i]))
		{
			set_var_line(cmd.words[i], &name, &var);
			if (!is_in(data->export, name))
				ft_expv_add_back(&data->export, ft_expv_new(var, name));
			else if (var && ft_strstr(cmd.words[i], "+="))
				change_var(&data, name, var, 1);
			else if (var)
				change_var(&data, name, var, 0);
		}
		i++;
	}
}

void	export(t_cmd cmd, t_data *data)
{
	parse_export(cmd, data);
	if (!cmd.words[1])
		export_print(data->export);
}
