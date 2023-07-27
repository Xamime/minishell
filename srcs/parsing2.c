/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:15:34 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/27 17:37:27 by jfarkas          ###   ########.fr       */
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
	if (!cmd->cmd_name || !cmd->cmd_name[0])
		return (NULL);
	path = get_path(expv);
	cmd->path = ft_split(path, ':');
	while (cmd->path[i])
	{
		tmp = ft_strjoin(cmd->path[i], "/");
		command = ft_strjoin(tmp, cmd->cmd_name);
		free(tmp);
		if (access(command, X_OK) == 0) // ou F_OK ? perror apres peut etre
			return (command);
		free(command);
		i++;
	}
	free_array(cmd->path);
	cmd->path = NULL;
	return (NULL);
}
