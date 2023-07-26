/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:15:34 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/25 23:03:31 by jfarkas          ###   ########.fr       */
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

char	*get_access(t_cmd *cmd, t_expv *expv)
{
	char	*path;
	int		i;
	char	*tmp;
	char	*command;

	i = 0;
	path = get_path(expv);
	cmd->path = ft_split(path, ':');
	while (cmd->path[i])
	{
		tmp = ft_strjoin(cmd->path[i], "/");
		command = ft_strjoin(tmp, cmd->cmd_name);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	free_array(cmd->path);
	return (NULL);
}
