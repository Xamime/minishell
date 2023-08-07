/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:46:33 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 01:39:00 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *cmd)
{
	char	**builtins;
	int		i;
	int		builtin;

	i = 0;
	builtin = 0;
	builtins = ft_split("pwd:echo:cd:exit:export:env:unset", ':');
	while (builtins[i])
	{
		if (!ft_strcmp(cmd, builtins[i]))
			builtin = 1;
		free(builtins[i]);
		i++;
	}
	free(builtins);
	return (builtin);
}

void	better_lstclear(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}
