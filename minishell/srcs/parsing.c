/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:27 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/25 16:59:23 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	char	**builtins;
	int		i;
	int		builtin;

	i = 0;
	builtin = 0;
	builtins = ft_split("pwd:echo:cd", ':');
	while (builtins[i])
	{
		if (!ft_strcmp(cmd, builtins[i]))
			builtin = 1;
		free(builtins[i]);
		i++;
	}
	free(builtins);
	return (builtin);
}

char	*get_path(t_data *data)
{
	t_expv *tmp;

	tmp = data->export;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
			break ;
		tmp = tmp->next;
	}
	return (tmp->var);
}

char	*get_access(t_cmd cmd, t_data *data)
{
	char	*path;
	int		i;
	char	*tmp;
	char	*command;
	
	i = 0;
	path = get_path(data);
	cmd.path = ft_split(path, ':');
	while (cmd.path[i++])
	{
		tmp = ft_strjoin(cmd.path[i], "/");
		command = ft_strjoin(tmp, cmd.cmd_name);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
	}
	return (NULL);
}

void	execution(t_cmd cmd, t_data *data)
{
	char	*command;

	if (pipe(cmd.fd1) == -1)
		ft_putstr_fd("error pipe 1\n", 2);
	if (pipe(cmd.fd2) == -1)
		ft_putstr_fd("error pipe 2\n", 2);
	command = get_access(cmd, data);
}

void	exec_cmd(t_cmd cmd, t_data *data)
{
	//if (is_builtin(cmd.cmd_name))
		exec_builtin(cmd, data);
	//else
		execution(cmd, data);
}

t_cmd	*init_cmds(char *cmd_line)
{
	t_cmd	*cmds;
	char	**sub_shells;
	int		i;

	i = 0;
	sub_shells = ft_split(cmd_line, '|');
	while (sub_shells[i])
		i++;
	cmds = malloc(sizeof(t_cmd) * (i + 1));
	i = 0;
	while (sub_shells[i])
	{
		cmds[i].cmd = sub_shells[i]; // a free
		cmds[i].infile = 0;
		cmds[i].outfile = 1;
		i++;
	}
	cmds[i].cmd = NULL;
	free(sub_shells);
	//free_all(sub_shells); // existe pas
	return (cmds);
}

void	split_pipe(t_data *data, t_cmd *cmds)
{
	int		i;

	i = 0;
	while (cmds[i].cmd)
	{
		cmds[i].redirs = malloc(sizeof(t_redir));
		init_redir(&cmds[i].redirs);
		set_heredocs(cmds[i]);
		parse_cmd(cmds[i], data);
		i++;
	}
}

/*Replace addr1 by addr2, free addr1.*/
void	replace_address(char **addr1, char *addr2)
{
	char	*tmp;

	tmp = *addr1;
	*addr1 = addr2;
	free(tmp);
}

int	parse_cmd(t_cmd	cmd, t_data *data)
{
	char	**splitted;
	char	*tmp;
	int		i;

	i = 0;
	// parse syntax errors
	// redirects
	// initialiser new_cmd
	if (parse_redir(cmd.cmd, &cmd.redirs, &cmd) == -1)
		return (1);
	cmd.cmd = make_dollars(cmd.cmd, data, 0);
	splitted = ft_split_v2(cmd.cmd, ' ');
	if (!splitted[0])
		return (2);
	while (splitted[i])
	{
		replace_address(&splitted[i], make_dollars(splitted[i], data, 1));
		replace_address(&splitted[i], set_without_quotes(splitted[i]));
		i++;
	}
	cmd.cmd_name = splitted[0];
	cmd.words = splitted;
	exec_cmd(cmd, data);
	free_array(splitted);
	free(cmd.cmd);
	if (cmd.redirs)
		free_redirects(cmd.redirs);
	return (0);
}
