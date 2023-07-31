/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:37:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/01 00:43:45 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "errno.h"

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
		printf_fd(2, "minishell: %s\n", strerror(errno));
		free(oldpwd);
	}
	else
		update_pwd(expv, oldpwd);
}
