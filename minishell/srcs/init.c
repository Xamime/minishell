/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:48:13 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/25 16:11:17 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expv	**init_env(char **env)
{
	t_expv	*tmp;
	t_expv	**export;
	char	*name;
	char	*var;
	int		i;

	i = 0;
	export = malloc(sizeof(t_expv *));
	*export = NULL;
	while (env[i])
	{
		name = ft_substr(env[i], 0, ft_strchrlen(env[i], '='));
		var = ft_substr(env[i], ft_strchrlen(env[i], '=') + 1,
				ft_strlen(ft_strchr(env[i], '=') + 1));
		tmp = ft_expv_new(var, name);
		ft_expv_add_back(export, tmp);
		i++;
	}
	return (export);
}
