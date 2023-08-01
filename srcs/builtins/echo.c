/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:38:16 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/01 21:15:05 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	echo2(int idx, t_cmd *cmd);

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
			break ;
		i++;
	}
	i = j;
	echo2(j, cmd);
	if (i < 2)
		printf("\n");
}

static void	echo2(int idx, t_cmd *cmd)
{
	while (cmd->words[idx])
	{
		printf("%s", cmd->words[idx]);
		if (cmd->words[idx + 1])
			printf(" ");
		idx++;
	}
}
