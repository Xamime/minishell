/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:15:40 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/05 19:09:05 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_code;

static void	parse_and_exec(t_cmd *cmds, int h_success, t_expv *expv)
{
	int	i;

	i = 0;
	while (cmds[i].cmd)
	{
		parse_cmd(&cmds[i], expv, h_success);
		i++;
	}
	if (!cmds[1].cmd && cmds[0].cmd_name && is_builtin(cmds[0].cmd_name))
		only_one_builtin(&expv, cmds);
	else
		split_pipe(&expv, cmds);
}

static void	minishell(t_cmd *cmds, char *cmd, t_expv *expv)
{
	int		error;
	int		h_success;

	if (cmd[0])
		add_history(cmd);
	error = syntax_errors(cmd);
	if (!error)
	{
		cmds = init_cmds(cmd);
		init_redirs(cmds);
		h_success = set_heredocs(cmds, expv);
		parse_and_exec(cmds, h_success, expv);
		free(cmds);
	}
	else
		free(cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	t_expv	*export;
	t_cmd	*cmds;

	(void)av;
	if (ac > 1)
		exit(127);
	cmd = NULL;
	cmds = NULL;
	export = init_env(env);
	while (1)
	{
		sig_handler(0);
		cmd = readline("Minishell -> ");
		sig_handler(1);
		if (!cmd)
			ctrl_d(export);
		minishell(cmds, cmd, export);
	}
	rl_clear_history();
	freelist(export);
}
