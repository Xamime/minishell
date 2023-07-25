/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:51:44 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/25 17:20:39 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_one(t_expv **list, t_expv *to_del)
{
	t_expv	*tmp;

	if (!list || !*list || !to_del)
		return ;
	tmp = *list;
	if (to_del == tmp)
		*list = to_del->next;
	else
	{
		while (tmp && tmp->next != to_del)
			tmp = tmp->next;
		tmp->next = to_del->next;
	}
	if (to_del->name)
		free(to_del->name);
	if (to_del->var && to_del->var[0])
		free(to_del->var);
	free(to_del);
}

t_expv	*ft_expv_last(t_expv *expv)
{
	if (expv == NULL)
		return (NULL);
	while (expv->next != NULL)
		expv = expv->next;
	return (expv);
}

t_expv	*ft_expv_new(char *var, char *name)
{
	t_expv	*elem;

	elem = ft_calloc(sizeof(t_expv), 1);
	if (!(elem))
		return (NULL);
	elem->next = NULL;
	elem->var = var;
	elem->name = name;
	return (elem);
}

void	ft_expv_add_back(t_expv **expv, t_expv *new)
{
	t_expv	*tmp;

	if (expv == NULL)
		return ;
	if (*expv == NULL)
	{
		*expv = new;
		return ;
	}
	tmp = ft_expv_last(*expv);
	tmp->next = new;
}

int	ft_expv_size(t_expv *expv)
{
	int	i;

	i = 0;
	while (expv != NULL)
	{
		expv = expv->next;
		i++;
	}
	return (i);
}
