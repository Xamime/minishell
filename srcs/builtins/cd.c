/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:37:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/27 12:01:35 by jfarkas          ###   ########.fr       */
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
			printf("minishell: cd: HOME not set\n");
		return ;
	}
	remove_last_nl(directory);
	if (chdir(directory) == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", directory);
		free(oldpwd);
	}
	else
		update_pwd(expv, oldpwd);
}
