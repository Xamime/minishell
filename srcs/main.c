/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:15:40 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/03 18:50:57 by marvin           ###   ########.fr       */
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

void	sig_handler(int sig)
{
	if (sig == SIGINT)
       printf("\nMinishell -> ");
    // else if (sig == SIGQUIT)
	// 	write(2, "\n", 1);
	// 	rl_replace_line("", 0);
	// 	rl_on_new_line();
	// 	rl_redisplay();
}

void	sig_handler2(int sig)
{
	int	fd;

	if (sig == SIGINT)
    {
		ft_putchar_fd('\n', 1);
		// fd = dup(0);
		//close(0);
		g_exit_code = 300;
		//write(2, "\n", 1);
		//dup2(fd, 0);
		//close(fd);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
}

int	sig_info(int mode)
{
	struct sigaction act;
	signal(SIGQUIT, SIG_IGN);
	if (mode == 1)
		act.sa_handler =  &sig_handler;
	else
		act.sa_handler = &sig_handler2;
	sigfillset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	// {
	// 	printf("not fail\n");
	// }

	return (0);
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

	//signal(SIGINT,SIG_DFL);
	(void)av;
	if (ac > 1)
		exit(127);
	cmd = NULL;
	cmds = NULL;
	sig_info(1);
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
