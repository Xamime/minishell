/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:24:32 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/02 14:25:39 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	only_one_builtin(t_expv **expv, t_cmd *cmd)
{
	int	real_in;
	int	real_out;
	int	real_fds[2];

	real_in = dup(0);
	real_out = dup(1);
	real_fds[0] = real_in;
	real_fds[1] = real_out;
	if (cmd->infile > -1)
		dup2(cmd->infile, 0);
	if (cmd->outfile > -1)
		dup2(cmd->outfile, 1);
	if (!cmd->error)
		exec_builtin(cmd, expv, NULL, real_fds);
	free_command(cmd);
	dup2(real_in, 0);
	close(real_in);
	dup2(real_out, 1);
	close(real_out);
	if (cmd->infile > -1)
		close(cmd->infile);
	if (cmd->outfile > -1)
		close(cmd->outfile);
	g_exit_code = cmd->status % 255;
}
