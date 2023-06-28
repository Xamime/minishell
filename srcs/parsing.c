/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:27 by mdesrose          #+#    #+#             */
/*   Updated: 2023/06/28 20:10:43 by mdesrose         ###   ########.fr       */
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
	env = malloc(sizeof(char *) * size + 1);
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

void	execution(t_cmd *cmd, t_data *data)
{
	char	*command;

	command = get_access(cmd, data);
	if (!command)
	{
		printf("Command not found\n");
		free(command);
	}
	else
		execve(command, cmd->words, ft_get_env(data));
}

void	exec_cmd(t_cmd *cmd, t_data *data)
{
	if (is_builtin(cmd->cmd_name))
		exec_builtin(*cmd, data);
	else
		execution(cmd, data);
}

void	set_pipes(int fd_in, int fd_out, int *pfd, int p_out)
{
	if (p_out > -1)
	{
		dup2(p_out, 0);
		close(p_out);
	}
	dup2(pfd[1], 1);
	close(pfd[1]);
	close(pfd[0]);
	if (fd_in > -1)
		dup2(fd_in, 0);
	close(fd_in);
	if (fd_out > -1)
		dup2(fd_out, 1);
	close(fd_out);
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

	i = 0;
	p_out = 0;
	init_heredoc(cmds);
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
			//init_redir(&cmds[i].redirs);
			parse_cmd(&cmds[i], data);
			set_pipes(cmds[i].infile, cmds[i].outfile, pfd, p_out);
			exec_cmd(&cmds[i], data);
			free_command(&cmds[i]);
			freelist(data->export);
			free(cmds);
			free(data);
			exit(0);
		}
		if (p_out != 0)
			close(p_out);
		if (cmds[i].infile > -1)
			close(cmds[i].infile);
		if (cmds[i].outfile > -1)
			close(cmds[i].outfile);
		p_out = dup(pfd[0]);
		close(pfd[1]);
		close(pfd[0]);
		wait(&chld_status);
		i++;
	}
	if (p_out != 0)
		close(p_out);
	i = 0;
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
	cmd->cmd = make_dollars(cmd->cmd, data, 0);
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
		free_redirects(cmd->redirs);
	return (0);
}
