/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:15:40 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/02 20:03:06 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

int	g_exit_code;

void	ctrl_d(t_expv *export, t_cmd *cmds)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	freelist(export);
	exit(0);
}

void	listen(int sig, siginfo_t *info, void *unused)
{
	(void)info;
	(void)unused;
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		return ;
	}
}

void	sig_info(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = listen;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

static void	minishell(t_cmd *cmds, char *cmd, t_expv *export)
{
	int		error;
	int		i;

	i = 0;
	add_history(cmd);
	error = syntax_errors(cmd);
	if (!error)
	{
		cmds = init_cmds(cmd);
		init_redirs(cmds);
		set_heredocs(cmds);
		while (cmds[i].cmd)
		{
			parse_cmd(&cmds[i], export);
			i++;
		}
		if (!cmds[1].cmd && cmds[0].cmd_name && is_builtin(cmds[0].cmd_name))
			only_one_builtin(&export, cmds);
		else
			split_pipe(&export, cmds);
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
		cmd = readline("Minishell -> ");
		if (!cmd)
			ctrl_d(export, cmds);
		minishell(cmds, cmd, export);
	}
	rl_clear_history();
	freelist(export);
}
