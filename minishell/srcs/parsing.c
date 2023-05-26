/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:27 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/26 15:57:42 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
		//execution(cmd, data);
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
		parse_cmd(&cmds[i], data);
		//exec_cmd(cmd[i], data);
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

int	parse_cmd(t_cmd	*cmd, t_data *data)
{
	char	**splitted;
	char	*tmp;
	int		i;

	i = 0;
	// parse syntax errors
	// redirects
	// initialiser new_cmd
	if (parse_redir(cmd->cmd, &cmd->redirs, cmd) == -1)
		return (1);
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
	free_array(splitted);
	//if (splitted[1])
	free(cmd->cmd);
	if (cmd->redirs)
		free_redirects(cmd->redirs);
	return (0);
}
