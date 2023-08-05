/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:38:16 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/05 15:33:57 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_n(t_cmd *cmd, int i)
{
	int	j;

	j = 1;
	if (ft_strncmp(cmd->words[i], "-n", 2))
		return (0);
	while (cmd->words[i][j])
	{
		if (cmd->words[i][j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

static int	skip_n(t_cmd *cmd)
{
	int	i;
	int	to_skip;

	i = 1;
	to_skip = 1;
	while (cmd->words[i])
	{
		if (check_n(cmd, i))
			to_skip++;
		else
			break ;
		i++;
	}
	return (to_skip);
}

void	echo(t_cmd *cmd)
{
	int	i;
	int	to_skip;

	if (!cmd->words[1])
	{
		printf_fd(1, "\n");
		return ;
	}
	to_skip = skip_n(cmd);
	i = to_skip;
	while (cmd->words[i])
	{
		printf_fd(1, "%s", cmd->words[i]);
		if (cmd->words[i + 1])
			printf_fd(1, " ");
		i++;
	}
	if (to_skip < 2)
		printf_fd(1, "\n");
}
