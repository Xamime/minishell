/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:42:51 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/31 22:49:08 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

void	set_heredocs(t_cmd *cmds)
{
	int		*fd;
	char	*filename;
	char	*tmp;
	char	*limiter;
	int		i;
	int		j;

	i = 0;
	while (cmds[i].cmd)
	{
		j = 0;
		while (cmds[i].cmd[j])
		{
			// mettre de quoi skip les quotes aussi
			if (is_in_set(cmds[i].cmd[j], "\"\'"))
				j += skip_quote(&cmds[i].cmd[j], cmds[i].cmd[j]);
			if (cmds[i].cmd[j] == '<' && cmds[i].cmd[j + 1] == '<')
			{
				fd = malloc(sizeof(int));
				filename = get_filename(&cmds[i].cmd[j], NULL);
				limiter = ft_strdup(filename); // bizarre
				*fd = heredoc_name(&cmds[i], &filename);
				while (1)
				{
					tmp = readline("> ");
					if (!ft_strncmp(tmp, limiter, ft_strlen(limiter) + 1))
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
			}
			j++;
		}
		i++;
	}
}

void	open_last_file(char *type, int *fd, char *filename, t_redir *redirs)
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

void	check_redirect(t_list *infile, t_cmd *cmd, t_list *heredoc)
{
	if (infile)
	{
		cmd->infile = *(int *)infile->content;
		if (heredoc)
			close(*(int *)heredoc->content);
	}
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
		if (is_in_set(cmd[i + j], "\"\'"))
			i += skip_and_copy(&cmd[i + j], &str[i], cmd[i + j], NULL);
		if (cmd[i + j] == '<' || cmd[i + j] == '>')
		{
			while (cmd[i + j] && is_in_set(cmd[i + j], "<>"))
				j++;
			while (cmd[i + j] && is_in_set(cmd[i + j], " \t\n"))
				j++;
			while (cmd[i + j] && !is_in_set(cmd[i + j], " \t\n<>"))
			{
				if (is_in_set(cmd[i + j], "\"\'"))
					j += skip_quote(&cmd[i + j], cmd[i + j]);
				j++;
			}
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

char	*remove_redir(t_cmd	*cmd)
{
	int		redirs_size;
	int		j;
	char	*str;

	str = cmd->cmd;
	redirs_size = 0;
	while (*str)
	{
		if (is_in_set(*str, "\"\'"))
			str = skip_to_char(str, *str);
		if (*str == '<' || *str == '>')
		{
			j = 0;
			while (*(str + j) && is_in_set(*(str + j), "<>"))
				j++;
			while (*(str + j) && is_in_set(*(str + j), " \t\n"))
				j++;
			while (*(str + j) && !is_in_set(*(str + j), " \t\n<>"))
			{
				if (is_in_set(*str, "\"\'"))
					j += skip_quote(str, *str);
				j++;
			}
			str += j;
			redirs_size += j;
		}
		if (*str && !is_in_set(*str, "<>"))
			str++;
	}
	//printf("redirs_size : %d\n", redirs_size);
	str = str_without_redir(str, cmd->cmd, redirs_size);
	//printf("str : %s\n", str);
	return (str);
}
