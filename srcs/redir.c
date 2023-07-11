/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:08:34 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/11 17:30:48 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Set Heredoc name, open and return fd
int	heredoc_name(t_cmd cmds, char *filename)
{
	int			fd;
	int			i;
	char		*tmp;
	char		*try;

	fd = 1;
	i = 0;
	replace_address(&filename, ft_strjoin("/tmp/", filename));
	while (1)
	{
		tmp = ft_itoa(i);
		try = ft_strjoin(filename, tmp);
		fd = open(try, O_RDONLY);
		free(tmp);
		if (fd == -1 && errno == ENOENT)
			break ;
		else if (errno != EACCES)
			close(fd);
		free(try);
		i++;
	}
	fd = open(try, O_CREAT | O_RDONLY, 0644);
	free(try);
	free(filename);
	return (fd);
}

int	secure_open(char *mode, char *filename)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(mode, "outfile"))
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(mode, "append"))
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (!ft_strcmp(mode, "infile"))
		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		exit(1);
	}
	return (fd);
}

void	add_redirect(t_redir *redirs, char *str)
{
	int		*fd;
	char	*filename;

	filename = get_filename(str);
	fd = malloc(sizeof(int));
	*fd = 0;
	if (*str == '>' && *(str + 1) != '>')
		open_last_file("outfile", fd, filename, redirs);
	else if (*str == '>' && *(str + 1) == '>')
		open_last_file("append", fd, filename, redirs);
	else if (*str == '<' && *(str + 1) != '<')
		open_last_file("infile", fd, filename, redirs);
	free(filename);
	if (*fd == 0)
		free(fd);
	// if (*fd == 0)
	// {
	// 	free(fd);
	// 	return (0);
	// }
	// return (*fd);
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

int	parse_redir(char *str, t_redir **redirs, t_cmd *cmd)
{
	char	*tmp;
	int		bool;

	bool = 0;
	tmp = str;
	while (*str)
	{
		if (*str == '<' || *str == '>')
		{
			bool = 1;
			// if (add_redirect(*redirs, str) == -1)
			// {
			// 	//free_redirects(*redirs);
			// 	return (-1);
			// }
			add_redirect(*redirs, str);
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
