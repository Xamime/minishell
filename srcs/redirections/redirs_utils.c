/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:42:51 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 17:15:39 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>

static int	secure_open(char *mode, char *filename)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(mode, "outfile"))
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(mode, "append"))
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(mode, "infile"))
		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf_fd(2, "minishell: ");
		perror(filename);
	}
	return (fd);
}

void	add_file(char *type, int *fd, char *filename, t_redir *redirs)
{
	*fd = secure_open(type, filename);
	if (*fd == -1)
		return ;
	if (!ft_strcmp(type, "outfile"))
		ft_lstadd_back(&redirs->outfiles, ft_lstnew(fd));
	if (!ft_strcmp(type, "append"))
		ft_lstadd_back(&redirs->outfiles, ft_lstnew(fd));
	if (!ft_strcmp(type, "infile"))
		ft_lstadd_back(&redirs->infiles, ft_lstnew(fd));
}

void	check_infile(t_list *infile, t_cmd *cmd, t_list *heredoc)
{
	if (infile)
	{
		cmd->infile = *(int *)infile->content;
		if (heredoc)
			close(*(int *)heredoc->content);
	}
}

int	find_last_infile(char *str)
{
	int		i;
	char	quote;

	i = ft_strlen(str) - 1;
	while (str[i] && str[i] != '<' && i > 0)
	{
		if (is_in_set(str[i], "\"\'"))
		{
			quote = str[i];
			i--;
			while (i > 0 && str[i] != quote)
				i--;
		}
		i--;
	}
	return (i);
}
