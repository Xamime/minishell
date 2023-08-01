/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:25:06 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/01 22:52:31 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_next_cmds_fds(t_cmd *cmds)
{
	int	i;

	i = 1;
	while (cmds[i].cmd)
	{
		if (cmds[i].infile > -1)
			close(cmds[i].infile);
		if (cmds[i].outfile > -1)
			close(cmds[i].outfile);
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

int	is_empty(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (!is_in_set(cmd_line[i], " \t\n"))
			return (0);
		i++;
	}
	return (1);
}

void	syntaxe_errors2(int error, char *err)
{
	if (error)
	{
		printf_fd(2, "bash: syntax error near unexpected token `%s'\n", err);
		g_exit_code = 2;
		free(err);
	}
}

int	check_single_quote(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (is_in_set(cmd_line[i], "\'\""))
		{
			if (!is_paired(&cmd_line[i], cmd_line[i]))
				return (1);
			i += skip_quote(&cmd_line[i], cmd_line[i]);
		}
		i++;
	}
	return (0);
}
