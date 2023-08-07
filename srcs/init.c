/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:48:13 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 17:25:33 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expv	*init_env(char **env)
{
	t_expv	*tmp;
	t_expv	*expv;
	char	*name;
	char	*var;
	int		i;

	i = 0;
	expv = NULL;
	while (env[i])
	{
		name = ft_substr(env[i], 0, ft_strchrlen(env[i], '='));
		var = ft_substr(env[i], ft_strchrlen(env[i], '=') + 1,
				ft_strlen(ft_strchr(env[i], '=') + 1));
		tmp = ft_expv_new(var, name);
		ft_expv_add_back(&expv, tmp);
		i++;
	}
	return (expv);
}

void	init_redirs(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].cmd)
	{
		cmds[i].redirs = malloc(sizeof(t_redir));
		cmds[i].redirs->infiles = NULL;
		cmds[i].redirs->outfiles = NULL;
		cmds[i].redirs->heredocs = NULL;
		cmds[i].redirs->heredoc_names = NULL;
		i++;
	}
}

static void	init_cmds2(char **sub_shells, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (sub_shells[i])
	{
		cmds[i].cmd = sub_shells[i];
		cmds[i].cmd_name = NULL;
		cmds[i].infile = -1;
		cmds[i].outfile = -1;
		cmds[i].pid = -1;
		cmds[i].status = 0;
		cmds[i].error = 0;
		cmds[i].id = i;
		i++;
	}
	cmds[i].cmd = NULL;
}

t_cmd	*init_cmds(char *cmd_line)
{
	t_cmd	*cmds;
	char	**sub_shells;
	int		i;

	i = 0;
	sub_shells = ft_split_quotes(cmd_line, "|");
	while (sub_shells[i])
		i++;
	cmds = malloc(sizeof(t_cmd) * (i + 1));
	init_cmds2(sub_shells, cmds);
	free(sub_shells);
	free(cmd_line);
	return (cmds);
}
