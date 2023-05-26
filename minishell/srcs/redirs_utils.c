/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:42:51 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/26 12:06:50 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_list(t_cmd *cmds, int *fd)
{
	ft_lstadd_back(&cmds->redirs->heredocs, ft_lstnew(fd));
}

void	set_heredocs(t_cmd cmds)
{
	int		*fd;
	char	*filename;
	char	*tmp;
	char	*tmp2;

	while (*cmds.cmd)
	{
		if (*cmds.cmd == '<' && *(cmds.cmd + 1) == '<')
		{
			fd = malloc(sizeof(int));
			filename = get_filename(cmds.cmd);
			tmp2 = get_filename(cmds.cmd);
			*fd = heredoc_name(cmds, filename);
			while (1)
			{
				tmp = readline("> ");
				if (!ft_strncmp(tmp, tmp2, ft_strlen(tmp2)))
					break ;
				ft_putstr_fd(tmp, *fd);
				free(tmp);
			}
			free(tmp);
			free(tmp2);
			make_list(&cmds, fd);
		}
		cmds.cmd++;
	}
}

int	*open_list(char *type, int *fd, char *filename, t_redir *redirs)
{
	*fd = secure_open(type, filename);
	ft_lstadd_back(&redirs->outfiles, ft_lstnew(fd));
	return (fd);
}

void	check_redirect(t_list *infile, t_cmd *cmd, t_list *heredoc)
{
	if (infile)
		cmd->infile = *(int *)infile->content;
	if (heredoc)
		close(*(int *)heredoc->content);
}
