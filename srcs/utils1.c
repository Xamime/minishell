/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:11:45 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/26 15:39:46 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	remove_last_nl(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[i - 1] == '\n')
		str[i - 1] = 0;
}

int	is_in(t_expv *list, char *str)
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

// return len from 0 to the char
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

int	check_plus_one(char c)
{
	if (!is_in_set(c, " \t\n"))
		return (1);
	return (0);
}
