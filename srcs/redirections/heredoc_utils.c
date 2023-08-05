/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:39:51 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/05 19:07:46 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>
#include <errno.h>

char	*get_heredoc_filename(char *str, int *exp_mode)
{
	int		size;
	char	*filename;

	while (is_in_set(*str, "<>"))
		str++;
	while (is_in_set(*str, " \t\n"))
		str++;
	size = 0;
	while (str[size] && !is_in_set(str[size], " \t\n<>"))
	{
		if (is_in_set(str[size], "\"\'"))
		{
			*exp_mode = 0;
			size += skip_quote(&str[size], str[size]) + 1;
		}
		else
			size++;
	}
	filename = ft_substr(str, 0, size);
	replace_address(&filename, set_without_quotes(filename));
	return (filename);
}

void	putstr_heredoc(char *tmp, int fd, int exp_mode, t_expv *expv)
{
	char	*str;

	if (exp_mode)
	{
		str = get_expanded_str_heredoc(tmp, expv);
		free(tmp);
		tmp = str;
	}
	ft_putstr_fd(tmp, fd);
	ft_putchar_fd('\n', fd);
	free(tmp);
}

int	heredoc_name(char **filename)
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
