/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:07:54 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/27 11:44:24 by jfarkas          ###   ########.fr       */
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