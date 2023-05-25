/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:59:53 by mdesrose          #+#    #+#             */
/*   Updated: 2023/04/25 15:49:07 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *str, t_data *data)
{
	t_expv	*tmp;

	tmp = data->export;
	while (tmp && ft_strcmp(str, tmp->name))
		tmp = tmp->next;
	if (tmp && tmp->var)
		return (tmp->var);
	return (NULL);
}

void	update_pwd(t_data *data, char *oldpwd)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * 4096);
	if (ft_getenv("OLDPWD", data))
	{
		if (ft_getenv("PWD", data))
		{
			change_var(&data, "OLDPWD", oldpwd, 0);
			change_var(&data, "PWD", getcwd(cwd, 4096), 0);
		}
		else
			change_var(&data, "OLDPWD", NULL, 0);
	}
	free(cwd); // a tcheck
}
