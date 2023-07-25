/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:29:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/25 15:41:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_redir2(char *cmd_line)
{
	int	i;
	int tru;

	tru = 0;
	i = 0;
	while (cmd_line && cmd_line[i])
	{
		while (is_in_set(cmd_line[i], "<>"))
		{
			tru = 1;
			i++;
		}
		while (cmd_line[i] == ' ')
			i++;
		if (tru && is_in_set(cmd_line[i], "<>"))
			return (1);
		i++;
	}
	return (0);
}

int	syntax_redir(char *cmd_line)
{
	int	i;

	i = 0;
	//if (is_in_set(cmd_line[0], "<>"))

	while (cmd_line && cmd_line[i])
	{
		if (is_in_set(cmd_line[i], "<>") && is_in_set(cmd_line[i + 1], "<>")
		&& is_in_set(cmd_line[i + 2], "<>"))
			return (1);
		if (is_in_set(cmd_line[i], "<>") && is_in_set(cmd_line[i + 1], "<>"))
		{
			i += 2;
			while (cmd_line[i] == ' ')
				i++;
		}
		if (!cmd_line[i] || is_in_set(cmd_line[i], "\n\0") )//|| syntax_redir2(cmd_line))
			return (1);
		i++;
	}
	return (0);
}

/*Return 1 if there is syntax error */
int	syntax_errors(char *cmd_line)
{
	int	i;
	int	is_empty;

	i = 0;
	is_empty = syntax_redir(cmd_line);
	if (is_empty && !is_in_set(cmd_line[0], "&|);"))
		is_empty = 1;
	// while(cmd_line && cmd_line[i])
	// {
	// 	if (!is_empty && !is_in_set(cmd_line[i], " \t\n"))
	// 		is_empty = 1;
	// 	i++;
	// }
	if (is_empty)
		EXIT_CODE = 2;
	return (is_empty);
}