/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:07:54 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/05 00:00:32 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset(t_cmd *cmd, t_expv **export)
{
	int		i;
	t_expv	*tmp;

	i = 1;
	while (cmd->words[i])
	{
		tmp = *export;
		while (tmp)
		{
			if (!ft_strcmp(cmd->words[i], tmp->name))
			{
				del_one(export, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}
