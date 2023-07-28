/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:17:30 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/28 12:21:19 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	exec_cmd(t_cmd *cmd, char **env, t_expv *expv)
{
	char	*command;

	if (is_builtin(cmd->cmd_name))
		exec_builtin(cmd, expv);
	else
	{
		command = get_access(cmd, expv);
		if (!command)
			return ;
		else
			execve(command, cmd->words, env);
		free(command);
	}
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
