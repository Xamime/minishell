/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:27 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 01:16:10 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	load_cmd(char **splitted, t_cmd *cmd, t_expv *expv)
{
	int	i;

	i = 0;
	if (!splitted[0])
	{
		if (!cmd->error)
			cmd->error = 2;
	}
	while (splitted[i])
	{
		replace_address(&splitted[i], make_dollars(splitted[i], expv, 1));
		replace_address(&splitted[i], set_without_quotes(splitted[i]));
		i++;
	}
	if (splitted[0])
		cmd->cmd_name = splitted[0];
	else
		cmd->cmd_name = "";
	cmd->words = splitted;
}

int	parse_cmd(t_cmd	*cmd, t_expv *expv, int h_success)
{
	char	**splitted;

	if (!h_success
		|| (h_success && parse_redir(cmd->cmd, &cmd->redirs, cmd, expv)))
	{
		if (!cmd->error)
			cmd->error = 1;
	}
	replace_address(&cmd->cmd, remove_redir(cmd));
	replace_address(&cmd->cmd, make_dollars(cmd->cmd, expv, 0));
	splitted = ft_split_quotes(cmd->cmd, " \t\n");
	load_cmd(splitted, cmd, expv);
	return (0);
}
