/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 01:15:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/07 01:16:48 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_empty(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (!is_in_set(cmd_line[i], " \t\n"))
			return (0);
		i++;
	}
	return (1);
}

void	syntaxe_errors2(int error, char *err)
{
	if (error)
	{
		printf_fd(2, "minishell: ");
		printf_fd(2, "syntax error near unexpected token `%s'\n", err);
		g_exit_code = 2;
		free(err);
	}
}

int	check_single_quote(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (is_in_set(cmd_line[i], "\'\""))
		{
			if (!is_paired(&cmd_line[i], cmd_line[i]))
			{
				printf_fd(2, "minishell: unclosed quote `%c'\n", cmd_line[i]);
				return (1);
			}
			i += skip_quote(&cmd_line[i], cmd_line[i]);
		}
		i++;
	}
	return (0);
}
