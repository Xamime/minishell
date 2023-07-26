/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:29:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/26 18:18:02 by jfarkas          ###   ########.fr       */
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

int		is_empty(char *cmd_line)
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

/*Return 1 if there is syntax error */
int	syntax_errors(char *cmd_line)
{
	int	i;
	int	error;

	i = 0;
	if (is_empty(cmd_line))
		return (-1);
	error = syntax_redir(cmd_line);
	if (error && !is_in_set(cmd_line[0], "&|);"))
		error = 1;
	// while(cmd_line && cmd_line[i])
	// {
	// 	if (!error && !is_in_set(cmd_line[i], " \t\n"))
	// 		error = 1;
	// 	i++;
	// }
	if (error)
		EXIT_CODE = 2;
	return (error);
}
