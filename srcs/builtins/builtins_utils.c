/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:06:33 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 18:01:00 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "errno.h"

char	*get_cwd_name(void)
{
	char	*dir;
	char	*buf;
	int		size;

	size = 10;
	dir = NULL;
	buf = NULL;
	while (dir == NULL)
	{
		if (buf)
			free(buf);
		buf = malloc(sizeof(char) * size);
		dir = getcwd(buf, size);
		if (!dir && errno != ERANGE)
		{
			free(buf);
			break ;
		}
		size += 50;
	}
	return (dir);
}

void	exec_builtin(t_cmd *cmd, t_expv **expv, char **env, int *real_fds)
{
	if (!ft_strcmp(cmd->cmd_name, "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->cmd_name, "cd"))
		cd(cmd->words[1], cmd, *expv);
	else if (!ft_strcmp(cmd->cmd_name, "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd->cmd_name, "exit"))
		ft_exit(env, cmd, expv, real_fds);
	else if (!ft_strcmp(cmd->cmd_name, "env"))
		print_env(cmd, *expv);
	else if (!ft_strcmp(cmd->cmd_name, "export"))
		export(cmd, expv);
	else if (!ft_strcmp(cmd->cmd_name, "unset"))
		unset(cmd, expv);
}
