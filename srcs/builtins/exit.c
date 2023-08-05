/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:56:07 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/05 14:58:24 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_exit_errors(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->words[1] && cmd->words[1][i])
	{
		if (!ft_isdigit(cmd->words[1][i])
		&& !is_in_set(cmd->words[1][i], "+-"))
		{
			printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				cmd->words[1]);
			return (2);
		}
		i++;
	}
	if (cmd->words[1] && cmd->words[2])
	{
		printf_fd(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

static int	check_code(t_cmd *cmd, int *err)
{
	char		*str;
	long long	code;
	int			i;

	code = ft_atoll(cmd->words[1]);
	str = ft_lltoa(code);
	i = 0;
	if (is_in_set(cmd->words[1][i], "+"))
		i++;
	if (ft_strcmp(&cmd->words[1][i], str))
	{
		printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			cmd->words[1]);
		*err = 2;
	}
	free(str);
	return (code);
}

static void	free_and_close(char **env, t_cmd *cmds, t_expv *expv, int *fds)
{
	free_fork(expv, cmds, env);
	if (fds)
	{
		close(fds[0]);
		close(fds[1]);
		if (fds[2] > -1)
			close(fds[2]);
		if (fds[3] > -1)
			close(fds[3]);
		free(fds);
	}
}

void	ft_exit(char **env, t_cmd *cmd, t_expv **expv, int *fds)
{
	long long	code;
	int			err;
	t_cmd		*cmds;

	ft_putstr_fd("exit\n", 1);
	cmds = cmd - cmd->id;
	err = check_exit_errors(cmd);
	if (!err && cmd->words[1])
		code = check_code(cmd, &err);
	else if (!err)
		code = 0;
	if (err == 1)
	{
		cmd->status = 1;
		return ;
	}
	free_and_close(env, cmds, *expv, fds);
	if (err)
		exit(err);
	exit((unsigned char)code);
}
