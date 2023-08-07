/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:57:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/07 15:55:30 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(t_cmd *cmd, t_expv *expv)
{
	t_expv	*tmp;

	if (cmd->words[1])
	{
		printf_fd(2, "minishell: env: too many arguments\n");
		cmd->status = 1;
		return ;
	}
	tmp = expv;
	while (tmp)
	{
		if (tmp->var)
			printf("%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
}
