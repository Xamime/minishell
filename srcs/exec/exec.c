/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:24:32 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/05 15:28:26 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	*load_fds(int in, int out, int infile, int outfile)
{
	int	*fds;

	fds = malloc(sizeof(int) * 4);
	fds[0] = in;
	fds[1] = out;
	fds[2] = infile;
	fds[3] = outfile;
	return (fds);
}

void	only_one_builtin(t_expv **expv, t_cmd *cmd)
{
	int	real_in;
	int	real_out;
	int	*fds;

	real_in = dup(0);
	real_out = dup(1);
	fds = load_fds(real_in, real_out, cmd->infile, cmd->outfile);
	if (cmd->infile > -1)
		dup2(cmd->infile, 0);
	if (cmd->outfile > -1)
		dup2(cmd->outfile, 1);
	if (!cmd->error)
		exec_builtin(cmd, expv, NULL, fds);
	free_command(cmd);
	free(fds);
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
