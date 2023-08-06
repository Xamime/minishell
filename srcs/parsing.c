/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:27 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/06 22:35:47 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "signal.h"

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

void	wait_childs(t_cmd *cmds)
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

void	close_after_fork(t_cmd *cmds, int *pfd, int *p_out, int index)
{
// printf("in : %d, out : %d\n", cmds[index].infile, cmds[index].outfile);
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

void	set_cmd(t_cmd *cmd, t_expv **expv, int *pipe_out, char **env)
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

void	split_pipe(t_expv **expv, t_cmd *cmds)
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

void	load_cmd(char **splitted, t_cmd *cmd, t_expv *expv)
{
	int	i;

	i = 0;
	if (!splitted[0])
	{
		if (!cmd->error)
			cmd->error = 2;
	}
	while (splitted[i])
	{
		replace_address(&splitted[i], make_dollars(splitted[i], expv, 1));
		replace_address(&splitted[i], set_without_quotes(splitted[i]));
		i++;
	}
	if (splitted[0])
		cmd->cmd_name = splitted[0];
	else
		cmd->cmd_name = "";
	cmd->words = splitted;
}

int	parse_cmd(t_cmd	*cmd, t_expv *expv, int h_success)
{
	char	**splitted;

	if (!h_success
		|| (h_success && parse_redir(cmd->cmd, &cmd->redirs, cmd, expv)))
	{
		if (!cmd->error)
			cmd->error = 1;
	}
	replace_address(&cmd->cmd, remove_redir(cmd));
	replace_address(&cmd->cmd, make_dollars(cmd->cmd, expv, 0));
	splitted = ft_split_quotes(cmd->cmd, " \t\n");
	load_cmd(splitted, cmd, expv);
	return (0);
}
