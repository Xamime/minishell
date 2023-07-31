/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:06:33 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/31 21:41:22 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(t_expv *expv, char *oldpwd)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * 4096);
	if (ft_getenv("OLDPWD", expv))
	{
		if (ft_getenv("PWD", expv))
		{
			change_var(expv, ft_strdup("OLDPWD"), oldpwd, 1);
			change_var(expv, ft_strdup("PWD"), getcwd(cwd, 4096), 0);
		}
		else
			change_var(expv, ft_strdup("OLDPWD"), NULL, 0);
	}
}

char	*get_cd_name(void)
{
	char	*dir;
	char	*buf;
	int		size;

	size = 50;
	dir = NULL;
	buf = NULL;
	while (dir == NULL)
	{
		if (buf)
			free(buf);
		buf = malloc(sizeof(char) * size);
		dir = getcwd(buf, size);
		size += 50;
	}
	return (dir);
}

int	check_n(t_cmd *cmd, int i)
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

void	print_env(t_expv *expv) // a bouger
{
	t_expv	*tmp;

	tmp = expv;
	while (tmp)
	{
		if (tmp->var)
			printf("%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
}

void	exec_builtin(t_cmd *cmd, t_expv **expv, char **env)
{
	if (!ft_strcmp(cmd->cmd_name, "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->cmd_name, "cd"))
		cd(cmd->words[1], *expv);
	else if (!ft_strcmp(cmd->cmd_name, "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd->cmd_name, "exit")) // a changer
	{
		ft_exit(env, cmd, expv);
		//exit(0);
	}
	else if (!ft_strcmp(cmd->cmd_name, "env"))
		print_env(*expv);
	else if (!ft_strcmp(cmd->cmd_name, "export"))
		export(cmd, expv);
	else if (!ft_strcmp(cmd->cmd_name, "unset"))
		unset(cmd, expv);
}
