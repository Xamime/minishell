/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:48:13 by mdesrose          #+#    #+#             */
/*   Updated: 2023/06/15 17:20:38 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expv	**init_env(char **env)
{
	t_expv	*tmp;
	t_expv	**export;
	char	*name;
	char	*var;
	int		i;

	i = 0;
	export = malloc(sizeof(t_expv *));
	*export = NULL;
	while (env[i])
	{
		name = ft_substr(env[i], 0, ft_strchrlen(env[i], '='));
		var = ft_substr(env[i], ft_strchrlen(env[i], '=') + 1,
				ft_strlen(ft_strchr(env[i], '=') + 1));
		tmp = ft_expv_new(var, name);
		ft_expv_add_back(export, tmp);
		i++;
	}
	return (export);
}

void	init_redir(t_redir **redirs)
{
	(*redirs)->heredocs = NULL;
	(*redirs)->infiles = NULL;
	(*redirs)->outfiles = NULL;
}

t_cmd	*init_cmds(char *cmd_line)
{
	t_cmd	*cmds;
	char	**sub_shells;
	int		i;

	i = 0;
	sub_shells = ft_split(cmd_line, '|');
	while (sub_shells[i])
		i++;
	cmds = malloc(sizeof(t_cmd) * (i + 1));
	i = 0;
	while (sub_shells[i])
	{
		cmds[i].cmd = sub_shells[i];
		cmds[i].infile = -1;
		cmds[i].outfile = -1;
		i++;
	}
	cmds[i].cmd = NULL;
	free(sub_shells);
	return (cmds);
}
