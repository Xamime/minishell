/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:38:16 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/31 16:59:33 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(t_cmd *cmd)
{
	int	i;
	int	j;

	j = 1;
	i = 1;
	if (!cmd->words[1])
	{
		printf("\n");
		return ;
	}
	while (cmd->words[i])
	{
		if (check_n(cmd, i))
			j++;
		else
			break;
		i++;
	}
	i = j;
	while (cmd->words[j])
	{
		ft_printf("%s", cmd->words[j]);
		if (cmd->words[j + 1])
			ft_printf(" ");
		j++;
	}
	if (i < 2)
		ft_printf("\n");
}
