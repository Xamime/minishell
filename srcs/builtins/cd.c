/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:37:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/07 17:03:59 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_pwd(t_expv *expv, char *oldpwd)
{
	if (ft_get_env_var("PWD", expv))
		change_var(expv, ft_strdup("PWD"), get_cwd_name(), 0);
	if (ft_get_env_var("OLDPWD", expv))
		change_var(expv, ft_strdup("OLDPWD"), oldpwd, 0);
	else
		free(oldpwd);
}

void	cd(char *directory, t_cmd *cmd, t_expv *expv)
{
	char	*oldpwd;

	if (!directory || (directory && cmd->words[2]))
	{
		if (directory)
			printf_fd(2, "minishell: cd: too many arguments\n");
		else
			printf_fd(2, "minishell: cd: too few arguments\n");
		cmd->status = 1;
		return ;
	}
	oldpwd = get_cwd_name();
	if (directory && chdir(directory) == -1)
	{
		cmd->status = 1;
		printf_fd(2, "minishell: cd: ");
		perror(directory);
		free(oldpwd);
	}
	else if (directory)
		update_pwd(expv, oldpwd);
}
