/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:26:00 by mdesrose          #+#    #+#             */
/*   Updated: 2023/03/21 17:37:32 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static void	ft_buftrim(char *buf)
{
	int	i;

	i = 0;
	if (ft_strchr(buf, '\n'))
	{
		ft_strcpy(buf, ft_strchr2(buf, '\n'));
		while (buf[i])
			i++;
		while (i < BUFFER_SIZE)
		{
			buf[i] = '\0';
			i++;
		}
	}	
	else
		ft_bzero(buf, BUFFER_SIZE + 1);
}

static char	*ft_strjoin_line(char const *line, char const *buf)
{
	char	*addline;
	int		i;
	int		linelen;
	int		buflen;

	linelen = ft_strlen_line(line, '\0');
	buflen = ft_strlen_line(buf, '\n');
	addline = malloc(sizeof(char) * (linelen + buflen + 1));
	if (addline == NULL)
		return (NULL);
	ft_strcpy(addline, line);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		addline[linelen + i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		addline[linelen + i] = '\n';
	addline[linelen + buflen] = '\0';
	return (addline);
}

static char	*ft_grow_line(char *line, char *buf)
{
	char	*addline;

	if (!buf[0] && !line)
		return (NULL);
	if (!line)
		addline = ft_substr(buf, 0, ft_strlen_line(buf, '\n'));
	else
		addline = ft_strjoin_line(line, buf);
	if (!addline)
		return (NULL);
	return (addline);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;
	int			end_check;

	buf[BUFFER_SIZE] = '\0';
	line = NULL;
	end_check = BUFFER_SIZE;
	while (!ft_strchr2(line, '\n') && end_check > 0)
	{
		tmp = line;
		if (!buf[0])
			end_check = read(fd, buf, BUFFER_SIZE);
		if (end_check < 0 && tmp)
		{
			free(tmp);
			return (NULL);
		}
		line = ft_grow_line(tmp, buf);
		ft_buftrim(buf);
		free(tmp);
	}
	return (line);
}
