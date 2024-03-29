/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:17:30 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/07 17:30:31 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <signal.h>

char	**ft_get_env(t_expv *export)
{
	int		size;
	char	**env;
	t_expv	*tmp;
	int		i;

	i = 0;
	tmp = export;
	size = ft_expv_size(export);
	env = malloc(sizeof(char *) * (size + 1));
	while (tmp)
	{
		if (tmp->var)
		{
			env[i] = ft_strdup(tmp->name);
			replace_address(&env[i], ft_strjoin(env[i], "="));
			replace_address(&env[i], ft_strjoin(env[i], tmp->var));
			i++;
		}
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

void	exec_cmd(t_cmd *cmds, char **env, t_expv **expv, int index)
{
	char	*command;
	int		child_status;

	close_next_cmds_fds(cmds);
	if (is_builtin(cmds[index].cmd_name))
		exec_builtin(&cmds[index], expv, env, NULL);
	else
	{
		signal(SIGPIPE, SIG_DFL);
		command = get_access(&cmds[index], *expv);
		if (command)
			execve(command, cmds[index].words, env);
		free(command);
	}
	child_status = cmds[index].status;
	free_fork(*expv, cmds, env);
	exit(child_status);
}

void	set_pipes(int fd_in, int fd_out, int *pfd, int pipe_out)
{
	if (pipe_out > 0)
	{
		dup2(pipe_out, 0);
		close(pipe_out);
	}
	dup2(pfd[1], 1);
	close(pfd[1]);
	close(pfd[0]);
	if (fd_in > -1)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (fd_out > -1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
}

int	get_exit_code(int status, t_cmd *cmd)
{
	if (g_exit_code == 130)
		return (g_exit_code);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		else if (WTERMSIG(status) == SIGQUIT)
			return (131);
	}
	else if (cmd->status)
		return (cmd->status);
	return (WEXITSTATUS(status));
}

void	close_after_fork(t_cmd *cmds, int *pfd, int *p_out, int index)
{
	if (*p_out > 0)
		close(*p_out);
	if (cmds[index].infile > -1)
		close(cmds[index].infile);
	if (cmds[index].outfile > -1)
		close(cmds[index].outfile);
	if (cmds[index + 1].cmd)
		*p_out = dup(pfd[0]);
	close(pfd[1]);
	close(pfd[0]);
}
