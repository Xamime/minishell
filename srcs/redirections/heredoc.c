/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:21:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/05 19:15:59 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>

int	write_heredoc(char *limiter, int fd, int exp_mode, t_expv *expv)
{
	int		error;
	char	*tmp;

	error = 0;
	while (1)
	{
		tmp = readline("> ");
		if (g_exit_code == 256 || !tmp
			|| (tmp && !ft_strncmp(tmp, limiter, ft_strlen(limiter) + 1)))
		{
			if (g_exit_code == 256)
			{
				g_exit_code = 130;
				error = 1;
			}
			else if (!tmp)
				printf_fd(2, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		putstr_heredoc(tmp, fd, exp_mode, expv);
	}
	if (tmp)
		free(tmp);
	return (error);
}

int	get_heredoc(t_cmd *cmds, int i, int j, t_expv *expv)
{
	int		*fd;
	char	*filename;
	char	*limiter;
	int		success;
	int		exp_mode;

	success = 1;
	exp_mode = 1;
	sig_handler(2);
	fd = malloc(sizeof(int));
	filename = get_heredoc_filename(&cmds[i].cmd[j], &exp_mode);
	limiter = ft_strdup(filename);
	*fd = heredoc_name(&filename);
	if (write_heredoc(limiter, *fd, exp_mode, expv))
		success = 0;
	close(*fd);
	*fd = open(filename, O_RDONLY, 0644);
	free(limiter);
	ft_lstadd_back(&cmds[i].redirs->heredocs, ft_lstnew(fd));
	ft_lstadd_back(&cmds[i].redirs->heredoc_names, ft_lstnew(filename));
	sig_handler(0);
	return (success);
}

int	set_heredocs(t_cmd *cmds, t_expv *expv)
{
	int		i;
	int		j;
	int		success;

	i = 0;
	success = 1;
	while (cmds[i].cmd && success)
	{
		j = 0;
		while (cmds[i].cmd[j] && success)
		{
			if (is_in_set(cmds[i].cmd[j], "\"\'"))
				j += skip_quote(&cmds[i].cmd[j], cmds[i].cmd[j]);
			if (cmds[i].cmd[j] == '<' && cmds[i].cmd[j + 1] == '<')
				success = get_heredoc(cmds, i, j, expv);
			j++;
		}
		i++;
	}
	if (!success)
	{
		// TOUT close merci bien aurevoir (cmds precedente error 3 + close tout ça tout ça)
		close_fds(cmds[i - 1].redirs->heredocs);
		close(*(int *)ft_lstlast(cmds[i - 1].redirs->heredocs)->content);
	}
	return (success);
}
