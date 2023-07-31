/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:58:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/31 16:59:39 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

int	test_dir(char *str, t_cmd *cmd)
{
	int	fd;
	int	is_dir;

	is_dir = 0;
	fd = open(str, O_DIRECTORY);
	if (fd > -1)
	{
		is_dir = 1;
		cmd->status = 126;
		close(fd);
	}
	if (is_dir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	return (is_dir);
}

char	*test_relative_path(char *str, t_cmd *cmd)
{
	if (test_dir(str, cmd))
		return (NULL);
	if (!cmd->status && !access(str, F_OK))
	{
		if (!access(str, X_OK))
			return (str);
		else
			cmd->status = 126;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (cmd->status == 126)
		ft_putstr_fd(": Permission denied\n", 2);
	else
	{
		cmd->status = 127;
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (NULL);
}

int	is_relative_path(char *str)
{
	if (str[0] == '/')
		return (1);
	else if (!ft_strncmp(str, "./", 2) || !ft_strncmp(str, "../", 3))
		return (1);
	return (0);
}

char	*test_absolute_path(char *name, char **path, t_cmd *cmd)
{
	int		i;
	char	*command;

	i = 0;
	command = NULL;
	while (path && path[i])
	{
		replace_address(&command, ft_strjoin(path[i], "/"));
		replace_address(&command, ft_strjoin(command, name));
		if (test_dir(command, cmd))
		{
			free(command);
			return (NULL);
		}
		if (!access(command, X_OK)) // ou F_OK ? perror apres peut etre
			return (command);
		i++;
	}
	cmd->status = 127;
	free(command);
	return (NULL);
}

char	*get_access(t_cmd *cmd, t_expv *expv)
{
	char	**path;
	char	*command;

	if (!cmd->cmd_name || !cmd->cmd_name[0])
	{
		cmd->status = 127;
		ft_putstr_fd(cmd->cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (NULL);
	}
	if (is_relative_path(cmd->cmd_name))
		return (test_relative_path(cmd->cmd_name, cmd));
	else
	{
		path = ft_split(ft_getenv("PATH", expv), ':');
		command = test_absolute_path(cmd->cmd_name, path, cmd);
	}
	free_array(path);
	if (command)
		return (command);
	else if (cmd->status == 127)
	{
		ft_putstr_fd(cmd->cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (NULL);
}
