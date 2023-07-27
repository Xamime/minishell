/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:59:53 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/27 18:27:17 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
