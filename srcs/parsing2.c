/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:15:34 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/27 20:12:45 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	char	**builtins;
	int		i;
	int		builtin;

	i = 0;
	builtin = 0;
	builtins = ft_split("pwd:echo:cd:exit:export:env:unset", ':');
	while (builtins[i])
	{
		if (!ft_strcmp(cmd, builtins[i]))
			builtin = 1;
		free(builtins[i]);
		i++;
	}
	free(builtins);
	return (builtin);
}
