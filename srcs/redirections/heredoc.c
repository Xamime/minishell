/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:21:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/02 21:54:05 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>
#include <errno.h>

// Set Heredoc name, open and return fd
int	heredoc_name(t_cmd *cmd, char **filename)
{
	int			fd;
	int			i;
	char		*tmp;
	char		*try;

	fd = 1;
	i = 0;
	try = NULL;
	replace_address(filename, ft_strjoin("/tmp/", *filename));
	while (1)
	{
		tmp = ft_itoa(i);
		replace_address(&try, ft_strjoin(*filename, tmp));
		fd = open(try, O_RDONLY);
		free(tmp);
		if (fd == -1 && errno == ENOENT)
			break ;
		else if (errno != EACCES)
			close(fd);
		i++;
	}
	fd = open(try, O_CREAT | O_WRONLY, 0644);
	free(*filename);
	*filename = try;
	return (fd);
}

void	set_heredocs(t_cmd *cmds)
{
	int		*fd;
	char	*filename;
	char	*tmp;
	char	*limiter;
	int		i;
	int		j;

	i = 0;
	sig_info(2);
	while (cmds[i].cmd)
	{
		j = 0;
		while (cmds[i].cmd[j])
		{
			if (is_in_set(cmds[i].cmd[j], "\"\'"))
				j += skip_quote(&cmds[i].cmd[j], cmds[i].cmd[j]);
			if (cmds[i].cmd[j] == '<' && cmds[i].cmd[j + 1] == '<')
			{
				fd = malloc(sizeof(int));
				filename = get_filename(&cmds[i].cmd[j], NULL, NULL);
				limiter = ft_strdup(filename); // bizarre
				*fd = heredoc_name(&cmds[i], &filename);
				while (1)
				{
					tmp = readline("> ");
					if (g_exit_code == 300)
						break ;
					if (!tmp)
					{
						printf_fd(2, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", limiter);
						break ;
					}
					if (tmp && !ft_strncmp(tmp, limiter, ft_strlen(limiter) + 1))
						break ;
					ft_putstr_fd(tmp, *fd);
					ft_putchar_fd('\n', *fd);
					free(tmp);
				}
				close(*fd);
				*fd = open(filename, O_RDONLY, 0644);
				free(tmp);
				free(limiter);
				ft_lstadd_back(&cmds[i].redirs->heredocs, ft_lstnew(fd));
				ft_lstadd_back(&cmds[i].redirs->heredoc_names, ft_lstnew(filename));
				//sig_info(1);
			}
			j++;
		}
		i++;
	}
}
