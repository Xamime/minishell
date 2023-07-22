/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:27 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/22 16:29:36 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_env(t_data *data)
{
	int		size;
	char	**env;
	t_expv	*tmp;
	int		i;

	i = 0;
	tmp = data->export;
	size = ft_expv_size(data->export);
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

void	execution(t_cmd *cmd, char **env, t_data *data)
{
	char	*command;

	command = get_access(cmd, data);
	if (!command)
	{
		printf("%s: command not found\n", cmd->cmd_name);
		free(command);
		free_array(cmd->words);
		free(cmd->cmd);
		free(cmd);
		freelist(data->export);
		free_array(env);
		free(data);
		exit(127);
	}
	else
		execve(command, cmd->words, env);
}

void	exec_cmd(t_cmd *cmd, char **env, t_data *data)
{
	if (is_builtin(cmd->cmd_name))
		exec_builtin(*cmd, data);
	else
		execution(cmd, env, data);
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

void	free_command(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->words && cmd->words[i])
	{
		free(cmd->words[i]);
		i++;
	}
	i = 0;
	while (cmd->path && cmd->path[i])
	{
		free(cmd->path[i]);
		i++;
	}
	free(cmd->cmd);
	cmd->cmd = NULL;
	free(cmd->words);
	free(cmd->path);
	cmd->words = NULL;
}

void	split_pipe(t_data *data, t_cmd *cmds)
{
	int		i;
	int		pfd[2];
	pid_t	pid;
	int		p_out;
	int		chld_status;
	char	**env;

	i = 0;
	p_out = 0;
	env = ft_get_env(data);
	init_redirs(cmds);
	set_heredocs(cmds);
	while (cmds[i].cmd)
	{
		if (pipe(pfd) == -1)
			ft_putstr_fd("error pipe 1\n", 2);
		if (!cmds[i + 1].cmd)
			dup2(1, pfd[1]);
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			parse_cmd(&cmds[i], data);
			set_pipes(cmds[i].infile, cmds[i].outfile, pfd, p_out);
			exec_cmd(&cmds[i], env, data);
			free_command(&cmds[i]);
			freelist(data->export);
			free(cmds);
			free(data);
			exit(0);
		}
		cmds[i].pid = pid;
		if (p_out > 0)
			close(p_out);
		if (cmds[i].infile > -1)
			close(cmds[i].infile);
		if (cmds[i].outfile > -1)
			close(cmds[i].outfile);
		p_out = dup(pfd[0]);
		close(pfd[1]);
		close(pfd[0]);
		free_redirects(cmds[i].redirs);
		unlink_heredocs(cmds);
		free(cmds[i].cmd);
		// wait(&chld_status);
		//waitpid(pid, &EXIT_CODE, 0);
		// EXIT_CODE = WEXITSTATUS(chld_status);
		i++;
	}
	if (p_out > 0)
		close(p_out);
	i = 0;
	while (cmds[i].cmd)
	{
		waitpid(cmds[i].pid, &cmds[i].status, 0);
		i++;
	}
	i = 0;
	while (cmds[i + 1].cmd)
		i++;
	printf("exit code : %d\n", cmds[i].status % 255);
	// pas sur que ce soit 255 mais ca a l'air de correspondre a bash
	// peut etre pas besoin de variable globale ? jsp
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

int	parse_cmd(t_cmd	*cmd, t_data *data)
{
	char	**splitted;
	char	*tmp;
	int		i;

	i = 0;
	// parse syntax errors
	// initialiser new_cmd
	if (parse_redir(cmd->cmd, &cmd->redirs, cmd) == -1)
		return (1);
	replace_address(&cmd->cmd, remove_redir(cmd, data));
	replace_address(&cmd->cmd, make_dollars(cmd->cmd, data, 0));
	splitted = ft_split_quotes(cmd->cmd, ' ');
	if (!splitted[0])
		return (2);
	while (splitted[i])
	{
		replace_address(&splitted[i], make_dollars(splitted[i], data, 1));
		replace_address(&splitted[i], set_without_quotes(splitted[i]));
		i++;
	}
	cmd->cmd_name = splitted[0];
	cmd->words = splitted;
	// free_array(splitted);
	//if (splitted[1])
	// free(cmd->cmd);
	if (cmd->redirs)
		free_redirects(cmd->redirs); // peut etre pas besoin
	return (0);
}
