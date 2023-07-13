/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:29:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/13 22:34:06 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_errors(char *cmd_line)
{
	int	i;
	int	is_empty;

	i = 0;
	is_empty = 1;
	while(cmd_line && cmd_line[i])
	{
		if (is_empty && !is_in_set(cmd_line[i], " \t\n"))
			is_empty = 0;
		i++;
	}
	if (is_empty)
		return (1);
	return (0);
}