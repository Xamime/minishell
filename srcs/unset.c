/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:07:54 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/25 17:20:53 by jfarkas          ###   ########.fr       */
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
				del_one(&data->export, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}
