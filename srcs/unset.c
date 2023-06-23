/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:07:54 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/26 12:10:25 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_cmd cmd, t_data *data)
{
	int		i;
	t_expv	*tmp;

	i = 1;
	while (cmd.words[i])
	{
		tmp = data->export;
		while (tmp)
		{
			if (!ft_strcmp(cmd.words[i], tmp->name))
			{
				del_one(data->export, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}
