/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:37:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/05 14:05:28 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "errno.h"

static void	update_pwd(t_expv *expv, char *oldpwd)
{
	if (ft_getenv("OLDPWD", expv))
	{
		if (ft_getenv("PWD", expv))
		{
			change_var(expv, ft_strdup("OLDPWD"), oldpwd, 1);
			change_var(expv, ft_strdup("PWD"), get_cd_name(), 0);
		}
		else
			change_var(expv, ft_strdup("OLDPWD"), NULL, 0);
	}
}

static int	cd_home(char *home, char *oldpwd, t_cmd *cmd, t_expv *expv)
{
	if (home)
	{
		chdir(home);
		update_pwd(expv, oldpwd);
		return (0);
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	cmd->status = 1;
	return (1);
}

void	cd(char *directory, t_cmd *cmd, t_expv *expv)
{
	char	*home;
	char	*oldpwd;

	if (cmd->words[1] && cmd->words[2])
	{
		printf_fd(2, "minishell: cd: too many arguments\n");
		cmd->status = 1;
		return ;
	}
	home = ft_getenv("HOME", expv);
	oldpwd = get_cd_name();
	if (directory == NULL && cd_home(home, oldpwd, cmd, expv))
		return ;
	if (chdir(directory) == -1)
	{
		cmd->status = 1;
		printf_fd(2, "minishell: cd: %s\n", strerror(errno));
		free(oldpwd);
	}
	else
		update_pwd(expv, oldpwd);
}
