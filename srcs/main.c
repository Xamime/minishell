/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:15:40 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/27 18:21:53 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

int	EXIT_CODE;

void	ctrl_d(t_expv *export, t_cmd *cmds)
{
	int i = 0;
	printf("exit\n");
	// while (cmds && cmds[i].cmd)
	// {
	// 	free(cmds[i].cmd);
	// 	i++;
	// }
	// free(cmds);
	freelist(export);
	// free(export);
	// free(data);
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
		printf("yo\n");
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

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	t_expv	*export;
	t_cmd	*cmds;
	int		error;

	(void)av;
	(void)ac; // erreur si args
	cmd = NULL;
	cmds = NULL;
	export = init_env(env);
	while (1)
	{
		sig_info();
		cmd = readline("Minishell -> ");
		if (!cmd || !ft_strcmp(cmd, "exit") /*|| cmd[0] == '\0'*/)
			ctrl_d(export, cmds);
		add_history(cmd);
		error = syntax_errors(cmd);
		if (!error)
		{
			cmds = init_cmds(cmd);
			init_redirs(cmds);
			set_heredocs(cmds);
			for (int i = 0; cmds[i].cmd; i++)
				parse_cmd(&cmds[i], export);
			if (!cmds[1].cmd && cmds[0].cmd_name && is_builtin(cmds[0].cmd_name))
				only_one_builtin(export, cmds);
			else
				split_pipe(export, cmds);
			free(cmds); // ?? normalement ca free toutes les commandes
		}
		else if (error > 0)
		{
			ft_putstr_fd("syntax error\n", 2);
			free(cmd);
		}
		else
			free(cmd);
	}
	rl_clear_history();
	freelist(export);
}
