/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:56:07 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/01 21:56:39 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_exit2(char *str, t_expv **expv, t_cmd *cmds);

void	ft_exit(char **env, t_cmd *cmds, t_expv **expv)
{
	long long	code;
	int			i;
	char		*str;

	i = 0;
	if (cmds->words[1] && cmds->words[2])
	{
		printf_fd(2, "minishell: exit: too many arguments\n");
		freelist(*expv);
		exit(1);
	}
	while (cmds->words[1] && cmds->words[1][i])
	{
		if (!ft_isdigit(cmds->words[1][i])
		&& !is_in_set(cmds->words[1][i], "+-"))
		{
			printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				cmds->words[1]);
			freelist(*expv);
			exit(2);
		}
		i++;
	}
	ft_exit2(str, expv, cmds);
}

static void	ft_exit2(char *str, t_expv **expv, t_cmd *cmds)
{
	long long	code;
	int			i;

	code = ft_atoll(cmds->words[1]);
	str = ft_lltoa(code);
	i = 0;
	while (is_in_set(cmds->words[1][i], "+"))
		i++;
	if (ft_strcmp(&cmds->words[1][i], str))
	{
		freelist(*expv);
		exit(2);
	}
	freelist(*expv);
	exit(code % 256);
}

void	set_exit_code(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i + 1].cmd)
		i++;
	// printf("exit code : %d\n", cmds[i].status % 255);
	g_exit_code = cmds[i].status % 255; // peut etre cast mais jsp en quoi
	i = 0;
	while (cmds[i].cmd)
	{
		free_command(&cmds[i]);
		i++;
	}
}
