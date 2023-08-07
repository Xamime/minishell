/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:24:32 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/07 17:23:07 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/wait.h>

static void	wait_childs(t_cmd *cmds)
{
	int		i;
	pid_t	wpid;
	int		status;

	i = 0;
	status = 0;
	while (cmds[i + 1].cmd)
		i++;
	waitpid(cmds[i].pid, &status, 0);
	g_exit_code = get_exit_code(status, &cmds[i]);
	wpid = 1;
	while (wpid > 0)
		wpid = wait(&status);
}

static void	set_cmd(t_cmd *cmd, t_expv **expv, int *pipe_out, char **env)
{
	int		pfd[2];
	t_cmd	*cmds;
	pid_t	pid;

	cmds = cmd - cmd->id;
	if (pipe(pfd) == -1)
		ft_putstr_fd("error pipe 1\n", 2);
	if (!(cmd + 1)->cmd)
		dup2(1, pfd[1]);
	if (!cmd->error)
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			set_pipes(cmd->infile, cmd->outfile, pfd, *pipe_out);
			exec_cmd(cmds, env, expv, cmd->id);
		}
		cmd->pid = pid;
	}
	close_after_fork(cmds, pfd, pipe_out, cmd->id);
}

void	exec_pipes(t_expv **expv, t_cmd *cmds)
{
	int		i;
	int		pipe_out;
	char	**env;

	i = 0;
	pipe_out = 0;
	env = ft_get_env(*expv);
	while (cmds[i].cmd)
	{
		set_cmd(&cmds[i], expv, &pipe_out, env);
		i++;
	}
	wait_childs(cmds);
	i = 0;
	while (cmds[i].cmd)
	{
		free_command(&cmds[i]);
		i++;
	}
	free_array(env);
}

static int	*load_fds(int in, int out, int infile, int outfile)
{
	int	*fds;

	fds = malloc(sizeof(int) * 4);
	fds[0] = in;
	fds[1] = out;
	fds[2] = infile;
	fds[3] = outfile;
	return (fds);
}

void	only_one_builtin(t_expv **expv, t_cmd *cmd)
{
	int	real_in;
	int	real_out;
	int	*fds;

	real_in = dup(0);
	real_out = dup(1);
	fds = load_fds(real_in, real_out, cmd->infile, cmd->outfile);
	if (cmd->infile > -1)
		dup2(cmd->infile, 0);
	if (cmd->outfile > -1)
		dup2(cmd->outfile, 1);
	if (!cmd->error)
		exec_builtin(cmd, expv, NULL, fds);
	free_command(cmd);
	free(fds);
	dup2(real_in, 0);
	close(real_in);
	dup2(real_out, 1);
	close(real_out);
	if (cmd->infile > -1)
		close(cmd->infile);
	if (cmd->outfile > -1)
		close(cmd->outfile);
	g_exit_code = cmd->status % 255;
}
