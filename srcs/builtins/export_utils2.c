/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:59:53 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 17:03:59 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_env_var(char *str, t_expv *expv)
{
	t_expv	*tmp;

	tmp = expv;
	while (tmp && ft_strcmp(str, tmp->name))
		tmp = tmp->next;
	if (tmp && tmp->var)
		return (tmp->var);
	return (NULL);
}
