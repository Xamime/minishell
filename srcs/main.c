/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:15:40 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/20 14:19:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

int	EXIT_CODE;

void	ctrl_d(t_data *data, t_expv *export, t_cmd *cmds)
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
	free(data);
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
	t_expv	*export;
	t_cmd	*cmds;

	(void)av;
	(void)ac; // erreur si args
	cmd = NULL;
	cmds = NULL;
	data = malloc(sizeof(t_data));
	export = init_env(env);
	data->export = export;
	while (1)
	{
		sig_info();
		cmd = readline("Minishell -> ");
		if (!cmd || !ft_strcmp(cmd, "exit") /*|| cmd[0] == '\0'*/)
			ctrl_d(data, export, cmds);
		add_history(cmd);
		if (!syntax_errors(cmd))
		{
			cmds = init_cmds(cmd);
			split_pipe(data, cmds);
			free(cmds);
		}
		else
			free(cmd);
		// printf("\n%s\n", make_dollars(str, data, 0));
		//free(cmds->cmd);
	}
	rl_clear_history();
	freelist(export);
	free(data);
}
