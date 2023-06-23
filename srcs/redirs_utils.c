/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:42:51 by mdesrose          #+#    #+#             */
/*   Updated: 2023/06/20 13:39:59 by mdesrose         ###   ########.fr       */
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

void	open_list(char *type, int *fd, char *filename, t_redir *redirs)
{
	*fd = secure_open(type, filename);
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

char	*change_str(char *str, char* cmd)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
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
		str[i] = '\0';
	}
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
	str = malloc(sizeof(char) * ft_strlen(cmd->cmd) - redirs_size);
	str = change_str(str, cmd->cmd);
	return (str);
}
