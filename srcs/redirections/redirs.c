/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:08:34 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/02 21:28:33 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int	add_redirect(t_redir *redirs, char *str, t_expv *expv, t_cmd *cmd)
{
	int		*fd;
	char	*filename;

	filename = get_filename(str, expv, cmd);
	if (cmd->status == 1)
		return (1);
	fd = malloc(sizeof(int));
	*fd = 0;
	if (*str == '>' && *(str + 1) != '>')
		open_last_file("outfile", fd, filename, redirs);
	else if (*str == '>' && *(str + 1) == '>')
		open_last_file("append", fd, filename, redirs);
	else if (*str == '<' && *(str + 1) != '<')
		open_last_file("infile", fd, filename, redirs);
	free(filename);
	if (*fd < 1)
		free(fd);
	if (*fd == 1)
	{
		cmd->status = 1;
		return (1);
	}
	return (0);
}

void	set_redirect(t_redir **redirs, char *str, t_cmd *cmd)
{
	t_list	*heredoc;
	t_list	*infile;
	t_list	*outfile;
	int		i;

	infile = ft_lstlast((*redirs)->infiles);
	heredoc = ft_lstlast((*redirs)->heredocs);
	outfile = ft_lstlast((*redirs)->outfiles);
	i = find_last_infile(str);
	if (i > 0 && str[i - 1] && str[i - 1] == '<')
	{
		cmd->infile = *(int *)heredoc->content;
		if (infile)
			close(*(int *)infile->content);
	}
	else if (i > 0)
		check_redirect(infile, cmd, heredoc);
	if (outfile)
		cmd->outfile = *(int *)outfile->content;
	close_fds((*redirs)->outfiles);
	close_fds((*redirs)->heredocs);
	close_fds((*redirs)->infiles);
}

static char	*go_to_next_redir(char *str)
{
	while (*str && is_in_set(*str, "<>"))
		str++;
	while (*str && is_in_set(*str, " \t\n"))
		str++;
	while (*str && !is_in_set(*str, " \t\n<>"))
	{
		if (is_in_set(*str, "\"\'"))
			str = skip_to_char(str, *str);
		str++;
	}
	return (str);
}

int	parse_redir(char *str, t_redir **redirs, t_cmd *cmd, t_expv *expv)
{
	char	*tmp;
	int		bool;

	bool = 0;
	tmp = str;
	while (*str)
	{
		// mettre de quoi skip les quotes
		if (*str && is_in_set(*str, "\"\'"))
			str = skip_to_char(str, *str);
		if (*str == '<' || *str == '>')
		{
			bool = 1;
			if (add_redirect(*redirs, str, expv, cmd))
				return (1);
			str = go_to_next_redir(str);
		}
		if (*str && !is_in_set(*str, "<>"))
			str++;
	}
	str = tmp;
	if (bool == 1)
		set_redirect(redirs, str, cmd);
	return (0);
}
