/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:27 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/29 17:54:23 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_exit_code(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i + 1].cmd)
		i++;
	// printf("exit code : %d\n", cmds[i].status % 255);
	EXIT_CODE = cmds[i].status % 255; // peut etre cast mais jsp en quoi
	i = 0;
	while (cmds[i].cmd)
	{
		free_command(&cmds[i]);
		i++;
	}
}

void	wait_childs(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].cmd)
	{
		if (!cmds[i].error)
			waitpid(cmds[i].pid, &cmds[i].status, 0);
		i++;
	}
}

void	close_after_fork(t_cmd *cmds, int *pfd, int *p_out, int index)
{
	if (*p_out > 0)
		close(*p_out);
	if (cmds[index].infile > -1) // si infile ou outfile = 0 ou 1 ?
		close(cmds[index].infile);
	if (cmds[index].outfile > -1)
		close(cmds[index].outfile);
	if (cmds[index + 1].cmd)
		*p_out = dup(pfd[0]);
	close(pfd[1]);
	close(pfd[0]);
}

void	random_function(t_cmd *cmds, t_expv *expv, int *pipe_out, int index)
{
	int		pfd[2];
	char	**env;
	int		child_status;
	pid_t	pid;

	env = ft_get_env(expv);
	if (pipe(pfd) == -1)
		ft_putstr_fd("error pipe 1\n", 2);
	if (!cmds[index + 1].cmd)
		dup2(1, pfd[1]);
	if (!cmds[index].error)
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			set_pipes(cmds[index].infile, cmds[index].outfile, pfd, *pipe_out);
			exec_cmd(cmds, env, expv, index);
			child_status = cmds[index].status;
			free_fork(expv, cmds, env);
			exit(child_status); // exit code erreur du builtin
		}
		cmds[index].pid = pid;
	}
	close_after_fork(cmds, pfd, pipe_out, index);
	free_array(env);
}

// void	random_function2()
// {
// 	int	i;
// 	int	pipe_out;

// 	i = 0;
// 	while (cmds[i].cmd)
// 	{
// 		if (pipe(pfd) == -1)
// 			ft_putstr_fd("error pipe 1\n", 2);
// 		if (!cmds[i + 1].cmd)
// 			dup2(1, pfd[1]);
// 		if (!cmds[i].error)
// 		{
// 			pid = fork();
// 			if (pid == -1)
// 				perror("fork");
// 			else if (pid == 0)
// 			{
// 				set_pipes(cmds[i].infile, cmds[i].outfile, pfd, pipe_out);
// 				exec_cmd(cmds, env, expv, i);
// 			}
// 			cmds[i].pid = pid;
// 		}
// 		close_after_fork(cmds, pfd, &pipe_out, i);
// 		i++;
// 	}
// }

void	split_pipe(t_expv *expv, t_cmd *cmds)
{
	int		i;
	int		pfd[2];
	pid_t	pid;
	int		pipe_out;
	int		chld_status;
	char	**env;

	i = 0;
	pipe_out = 0;
	env = ft_get_env(expv);
	while (cmds[i].cmd)
	{
		// random_function(cmds, expv, &pipe_out, i);
		if (pipe(pfd) == -1)
			ft_putstr_fd("error pipe 1\n", 2);
		if (!cmds[i + 1].cmd)
			dup2(1, pfd[1]);
		if (!cmds[i].error)
		{
			pid = fork();
			if (pid == -1)
				perror("fork");
			else if (pid == 0)
			{
				set_pipes(cmds[i].infile, cmds[i].outfile, pfd, pipe_out);
				exec_cmd(cmds, env, expv, i);
			}
			cmds[i].pid = pid;
		}
		close_after_fork(cmds, pfd, &pipe_out, i);
		i++;
	}
	wait_childs(cmds);
	set_exit_code(cmds);
	free_array(env);
}

/*Replace addr1 by addr2, free addr1.*/
void	replace_address(char **addr1, char *addr2)
{
	char	*tmp;

	tmp = *addr1;
	*addr1 = addr2;
	free(tmp);
}

int	parse_cmd(t_cmd	*cmd, t_expv *expv)
{
	char	**splitted;
	char	*tmp;
	int		i;

	i = 0;
	// parse syntax errors
	// initialiser new_cmd
	if (parse_redir(cmd->cmd, &cmd->redirs, cmd))
		cmd->error = 1;
	replace_address(&cmd->cmd, remove_redir(cmd));
	replace_address(&cmd->cmd, make_dollars(cmd->cmd, expv, 0));
	splitted = ft_split_quotes(cmd->cmd, ' ');
	if (!splitted[0])
		cmd->error = 2;
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
	return (0);
}
