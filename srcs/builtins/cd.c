/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:37:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/27 15:25:03 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd(char *directory, t_expv *expv)
{
	char	*home;
	char	*oldpwd;

	home = ft_getenv("HOME", expv);
	oldpwd = get_cd_name();
	if (directory == NULL)
	{
		if (home)
		{
			chdir(home);// a voir
			update_pwd(expv, oldpwd);
		}
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return ;
	}
	remove_last_nl(directory);
	if (chdir(directory) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(directory, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(oldpwd);
	}
	else
		update_pwd(expv, oldpwd);
}
