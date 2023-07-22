/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:42:51 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/22 14:49:31 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

void	make_list(t_cmd *cmds, int *fd)
{
	ft_lstadd_back(&cmds->redirs->heredocs, ft_lstnew(fd));
}

void	set_heredocs(t_cmd *cmds)
{
	int		*fd;
	char	*filename;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	while (cmds[i].cmd)
	{
		j = 0;
		while (cmds[i].cmd[j])
		{
			if (cmds[i].cmd[j] == '<' && cmds[i].cmd[j + 1] == '<')
			{
				fd = malloc(sizeof(int));
				filename = get_filename(&cmds[i].cmd[j]);
				tmp2 = get_filename(&cmds[i].cmd[j]);
				*fd = heredoc_name(cmds[i], filename);
				while (1)
				{
					tmp = readline("> ");
					if (!ft_strncmp(tmp, tmp2, ft_strlen(tmp2) + 1))
						break ;
					ft_putstr_fd(tmp, *fd);
					printf("gnl2 : %s\n", get_next_line(*fd));
					free(tmp);
				}
				close(*fd);
				*fd = open(filename, O_RDONLY, 0644);
				free(tmp);
				free(tmp2);
				make_list(cmds, fd);
			}
			j++;
		}
		i++;
	}
}

void	open_last_file(char *type, int *fd, char *filename, t_redir *redirs)
{
	*fd = secure_open(type, filename);
	printf("%d fd, %s gnl\n", *fd, get_next_line(*fd));
	if (!ft_strcmp(type, "outfile"))
		ft_lstadd_back(&redirs->outfiles, ft_lstnew(fd));
	if (!ft_strcmp(type, "append"))
		ft_lstadd_back(&redirs->outfiles, ft_lstnew(fd));
	if (!ft_strcmp(type, "infile"))
		ft_lstadd_back(&redirs->infiles, ft_lstnew(fd));
}

void	check_redirect(t_list *infile, t_cmd *cmd, t_list *heredoc)
{
	if (infile)
		cmd->infile = *(int *)infile->content;
	if (heredoc)
		close(*(int *)heredoc->content);
}

char	*str_without_redir(char *str, char* cmd, int redirs_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * ft_strlen(cmd) - redirs_size + 1);
	while (cmd[i + j])
	{
		if (cmd[i + j] == '<' || cmd[i + j] == '>')
		{
			while (cmd[i + j] && is_in_set(cmd[i + j], "<>"))
				j++;
			while (cmd[i + j] && is_in_set(cmd[i + j], " \t\n"))
				j++;
			while (cmd[i + j] && !is_in_set(cmd[i + j], " \t\n<>"))
				j++;
		}
		if (cmd[i + j] && !is_in_set(cmd[i + j], "<>"))
		{
			str[i] = cmd[i + j];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}

char	*remove_redir(t_cmd	*cmd, t_data *data)
{
	int		redirs_size;
	int		j;
	char	*str;

	str = cmd->cmd;
	redirs_size = 0;
	while (*str)
	{
		if (*str == '<' || *str == '>')
		{
			j = 0;
			while (*(str + j) && is_in_set(*(str + j), "<>"))
				j++;
			while (*(str + j) && is_in_set(*(str + j), " \t\n"))
				j++;
			while (*(str + j) && !is_in_set(*(str + j), " \t\n<>"))
				j++;
			str += j;
			redirs_size += j;
		}
		if (*str && !is_in_set(*str, "<>"))
			str++;
	}
	str = str_without_redir(str, cmd->cmd, redirs_size);
	return (str);
}
