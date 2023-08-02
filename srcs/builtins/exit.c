/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:56:07 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/02 17:04:22 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static void	ft_exit2(char *str, t_expv **expv, t_cmd *cmds);

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
	char	*str;
	int		code;
	int		i;

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

static void	free_and_close(char **env, t_cmd *cmds, t_expv *expv, int *real_fds)
{
	free_fork(expv, cmds, env);
	if (real_fds)
	{
		close(real_fds[0]);
		close(real_fds[1]);
	}
}

void	ft_exit(char **env, t_cmd *cmd, t_expv **expv, int *real_fds)
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
	free_and_close(env, cmds, *expv, real_fds);
	if (err)
		exit(err);
	exit((unsigned char)code);
}

void	set_exit_code(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i + 1].cmd)
		i++;
	g_exit_code = cmds[i].status;
	i = 0;
	while (cmds[i].cmd)
	{
		free_command(&cmds[i]);
		i++;
	}
}
