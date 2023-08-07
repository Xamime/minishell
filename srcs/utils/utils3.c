/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:25:06 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 01:44:54 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_next_cmds_fds(t_cmd *cmds)
{
	int	i;

	i = 1;
	while (cmds[i].cmd)
	{
		if (cmds[i].infile > -1)
			close(cmds[i].infile);
		if (cmds[i].outfile > -1)
			close(cmds[i].outfile);
		i++;
	}
}

void	replace_address(char **addr1, char *addr2)
{
	char	*tmp;

	tmp = *addr1;
	*addr1 = addr2;
	free(tmp);
}

void	ctrl_d(t_expv *export)
{
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	freelist(export);
	exit(130);
}
