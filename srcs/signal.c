/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:52:45 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/06 22:15:29 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>
#include <sys/ioctl.h>

static void	parent_sigint_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_exit_code = 256;
	close(0);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	child_sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
}

static void	child_sigquit_handler(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}

void	sig_handler(int mode)
{
	signal(SIGPIPE, SIG_IGN);
	if (mode == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &parent_sigint_handler);
	}
	else if (mode == 1)
	{
		signal(SIGQUIT, &child_sigquit_handler);
		signal(SIGINT, &child_sigint_handler);
	}
	else if (mode == 2)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &heredoc_sigint_handler);
	}
}
