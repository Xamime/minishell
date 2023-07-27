/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:20:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/27 21:41:11 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	freelist(t_expv *export)
{
	t_expv *tmp;

	while (export)
	{
		tmp = export;
		export = export->next;
		free(tmp->name);
		free(tmp->var);
		free(tmp);
	}
	free(export);
}

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

void	free_command(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->words && cmd->words[i])
	{
		free(cmd->words[i]);
		i++;
	}
	free(cmd->cmd);
	cmd->cmd = NULL;
	free(cmd->words);
	free_redirects(cmd->redirs);
	cmd->words = NULL;
}

void	free_fork(t_expv *expv, t_cmd *cmds, char **env)
{
	int	i;

	i = 0;
	while (cmds[i].cmd)
	{
		free_command(&cmds[i]);
		i++;
	}
	freelist(expv);
	free(cmds);
	free_array(env);
}

void	free_redirects(t_redir *redirs)
{
	better_lstclear(redirs->heredocs);
	better_lstclear(redirs->infiles);
	better_lstclear(redirs->outfiles);
	unlink_heredocs(redirs->heredoc_names);
	better_lstclear(redirs->heredoc_names);
	free(redirs);
}
