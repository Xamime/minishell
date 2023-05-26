/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:15:40 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/26 15:58:21 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void	ctrl_d(t_data *data, t_expv **export, t_cmd *cmds)
{
	int i = 0;
	printf("exit\n");
	freelist(*export);
	free(export);
	free(data);
	if (cmds)
		while (cmds[i++].cmd)
			free(cmds[i].cmd);
	free(cmds);
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

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	t_data	*data;
	t_expv	**export;
	t_cmd	*cmds;

	(void)av;
	(void)ac;
	cmd = NULL;
	cmds = NULL;
	data = malloc(sizeof(t_data));
	export = init_env(env);
	data->export = *export;
	//char *str = "hello \"\'$USER\'\" \'$USER\' la $ $toto famille$polo$cul";
	while (1)
	{
		sig_info();
		cmd = readline("Minishell -> ");
		if (!cmd)
			ctrl_d(data, export, cmds);
		add_history(cmd);
		cmds = init_cmds(cmd);
		split_pipe(data, cmds);
		// printf("\n%s\n", make_dollars(str, data, 0));
		//free(cmds->cmd);
	}
	rl_clear_history();
	freelist(*export);
	free(data);
}
