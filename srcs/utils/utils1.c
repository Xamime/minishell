/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:11:45 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 01:13:58 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_in_expv(t_expv *list, char *str)
{
	int		found;
	t_expv	*ptr;

	found = 0;
	ptr = list;
	while (ptr)
	{
		if (ptr->name)
		{
			if (!ft_strncmp(ptr->name, str, ft_strlen(str)))
				found = 1;
			ptr = ptr->next;
		}
	}
	return (found);
}

int	ft_strchrlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}
