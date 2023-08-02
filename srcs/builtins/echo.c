/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:38:16 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/02 17:39:47 by jfarkas          ###   ########.fr       */
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
		printf_fd(1, "\n");
}

static void	echo2(int idx, t_cmd *cmd)
{
	while (cmd->words[idx])
	{
		printf_fd(1, "%s", cmd->words[idx]);
		if (cmd->words[idx + 1])
			printf_fd(1, " ");
		idx++;
	}
}
