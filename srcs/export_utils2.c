/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:59:53 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/25 22:50:23 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *str, t_expv *expv)
{
	t_expv	*tmp;

	tmp = expv;
	while (tmp && ft_strcmp(str, tmp->name))
		tmp = tmp->next;
	if (tmp && tmp->var)
		return (tmp->var);
	return (NULL);
}

void	update_pwd(t_expv *expv, char *oldpwd)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * 4096);
	if (ft_getenv("OLDPWD", expv))
	{
		if (ft_getenv("PWD", expv))
		{
			change_var(expv, "OLDPWD", oldpwd, 0);
			change_var(expv, "PWD", getcwd(cwd, 4096), 0);
		}
		else
			change_var(expv, "OLDPWD", NULL, 0);
	}
	// free(cwd); // a tcheck
}
