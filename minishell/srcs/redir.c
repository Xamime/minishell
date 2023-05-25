/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:08:34 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/25 14:43:49 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char	*get_filename(char *str)
{
	int		size;
	char	*filename;

	while (is_in_set(*str, "<>"))
		str++;
	while (is_in_set(*str, " \t\n"))
		str++;
	size = 0;
	while (str[size] && !is_in_set(str[size], " \t\n<>"))
		size++;
	filename = ft_substr(str, 0, size);
	return (filename);
}

void	make_list(t_cmd *cmds, int *fd)
{
	ft_lstadd_back(&cmds->redirs->heredocs, ft_lstnew(fd));
}

// Set Heredoc name, open and return fd
int		heredoc_name(t_cmd cmds, char *filename)
{
	int			fd;
	static int	i;
	char		*tmp;
	char		*tmp2;

	tmp = filename;
	filename = ft_strjoin("/tmp/", filename);
	free(tmp);
	tmp = filename;
	tmp2 = ft_itoa(i);
	filename = ft_strjoin(filename, tmp2);
	free(tmp);
	free(tmp2);
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	free(filename);
	i++;
	return (fd);
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

int	secure_open(char *mode, char *filename)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(mode, "outfile"))
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			perror(filename);
	}
	else if (!ft_strcmp(mode, "append"))
	{
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			perror(filename);
	}
	else if (!ft_strcmp(mode, "infile"))
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			perror(filename);
	}
	return (fd);
}

int	add_redirect(t_redir *redirs, char *str)
{
	int		*fd;
	char	*filename;

	filename = get_filename(str);
	fd = malloc(sizeof(int));
	*fd = 0;
	if (*str == '>' && *(str + 1) != '>')
	{
		*fd = secure_open("outfile", filename);
		ft_lstadd_back(&redirs->outfiles, ft_lstnew(fd));
	}
	else if (*str == '>' && *(str + 1) == '>')
	{
		*fd = secure_open("append", filename);
		ft_lstadd_back(&redirs->outfiles, ft_lstnew(fd));
	}
	else if (*str == '<' && *(str + 1) != '<')
	{
		*fd = secure_open("infile", filename);
		ft_lstadd_back(&redirs->infiles, ft_lstnew(fd));
	}
	free(filename);
	if (*fd == 0)
	{
		free(fd);
		return (0);
	}
	return (*fd);
}

void	close_fds(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->next)
			if (tmp->content)
				close(*(int *)tmp->content);
		tmp = tmp->next;
	}
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
	i = ft_strlen(str) - 1;
	while (str[i] && str[i] != '<' && i > 0)
		i--;
	printf("%d\n",i);
	if (str[i - 1] && str[i - 1] == '<')
	{
		cmd->infile = *(int *)heredoc->content;
		if (infile)
			close(*(int *)infile->content);
	}
	else
	{
		if (infile)
			cmd->infile = *(int *)infile->content;
		if (heredoc)
			close(*(int *)heredoc->content);	
	}
	if (outfile)
		cmd->outfile = *(int *)outfile->content;
	close_fds((*redirs)->outfiles);
	close_fds((*redirs)->heredocs);
	close_fds((*redirs)->infiles);
}

void	better_lstclear(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	free_redirects(t_redir *redirs)
{
	better_lstclear(redirs->heredocs);
	better_lstclear(redirs->infiles);
	better_lstclear(redirs->outfiles);
	free(redirs);
}

void	init_redir(t_redir **redirs)
{
	(*redirs)->heredocs = NULL;
	(*redirs)->infiles = NULL;
	(*redirs)->outfiles = NULL;
}

int	parse_redir(char *str, t_redir **redirs, t_cmd *cmd)
{
	char	*tmp;
	int		bool;

	bool = 0;
	tmp = str;
	// *redirs = malloc(sizeof(t_redir));
	// init_redir(redirs);}
	while (*str)
	{
		if (*str == '<' || *str == '>')
		{
			bool = 1;
			if (add_redirect(*redirs, str) == -1)
			{
				free_redirects(*redirs);
				return (-1);
			}
			while (*str && is_in_set(*str, "<>"))
				str++;
			while (*str && is_in_set(*str, " \t\n"))
				str++;
			while (*str && !is_in_set(*str, " \t\n<>"))
				str++;
		}
		if (*str && !is_in_set(*str, "<>"))
			str++;
	}
	str = tmp;
	if (bool == 1)
		set_redirect(redirs, str, cmd);
	return (0);
}

// void	lol(t_redirects *redirs)
// {
// 	t_list	*tmp;
// 	int		fd;

// 	tmp = redirs.outfiles;
// 	fd = -1;
// 	while (tmp)
// 	{
// 		fd = *((int *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	if (fd > -1)
// 		dup2(fd, 1);
// }