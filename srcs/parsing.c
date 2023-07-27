/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:27 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/27 21:40:47 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		env[i] = ft_strdup(tmp->name);
		replace_address(&env[i], ft_strjoin(env[i], "="));
		replace_address(&env[i], ft_strjoin(env[i], tmp->var));
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

void	execution(t_cmd *cmd, char **env, t_expv *expv)
{
	char	*command;

	command = get_access(cmd, expv);
	if (!command)
		return ;
	else
		execve(command, cmd->words, env);
	free(command);
}

void	exec_cmd(t_cmd *cmd, char **env, t_expv *expv)
{
	if (is_builtin(cmd->cmd_name))
		exec_builtin(cmd, expv);
	else
		execution(cmd, env, expv);
}

void	set_pipes(int fd_in, int fd_out, int *pfd, int p_out)
{
	if (p_out > 0)
	{
		dup2(p_out, 0);
		close(p_out);
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

void	split_pipe(t_expv *expv, t_cmd *cmds)
{
	int		i;
	int		pfd[2];
	pid_t	pid;
	int		p_out;
	int		chld_status;
	char	**env;

	i = 0;
	p_out = 0;
	env = ft_get_env(expv);
	while (cmds[i].cmd)
	{
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
				set_pipes(cmds[i].infile, cmds[i].outfile, pfd, p_out);
				exec_cmd(&cmds[i], env, expv);
				chld_status = cmds[i].status;
				free_fork(expv, cmds, env);
				exit(chld_status); // exit code erreur du builtin
			}
			cmds[i].pid = pid;
		}
		if (p_out > 0)
			close(p_out);
		if (cmds[i].infile > -1) // si infile ou outfile = 0 ou 1 ?
			close(cmds[i].infile);
		if (cmds[i].outfile > -1)
			close(cmds[i].outfile);
		p_out = dup(pfd[0]);
		close(pfd[1]);
		close(pfd[0]);
		i++;
	}
	if (p_out > 0)
		close(p_out);
	i = 0;
	while (cmds[i].cmd)
	{
		if (!cmds[i].error)
			waitpid(cmds[i].pid, &cmds[i].status, 0);
		i++;
	}
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
