/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:07:54 by mdesrose          #+#    #+#             */
/*   Updated: 2023/04/18 19:35:07 by mdesrose         ###   ########.fr       */
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
			if (!ft_strncmp(cmd.words[i], tmp->name,
				ft_strlen(cmd.words[i])))
			{
				del_one(data->export, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}
