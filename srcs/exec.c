/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:24:32 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/23 14:47:45 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	only_one_builtin(t_data *data, t_cmd *cmd)
{
	int	real_in;
	int	real_out;

	real_in = dup(0);
	real_out = dup(1);
	if (cmd->infile > -1)
		dup2(cmd->infile, 0);
	if (cmd->outfile > -1)
		dup2(cmd->outfile, 1);
	exec_builtin(*cmd, data);
	free_command(cmd);
	free_redirects(cmd->redirs);
	dup2(real_in, 0);
	close(real_in);
	dup2(real_out, 1);
	close(real_out);
	if (cmd->infile > -1)
		close(cmd->infile);
	if (cmd->outfile > -1)
		close(cmd->outfile);
	EXIT_CODE = cmd->status % 255;
}
