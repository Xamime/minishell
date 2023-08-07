/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:28:09 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/07 17:16:32 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	go_to_next_redir_it(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_in_set(str[i], "<>"))
		i++;
	while (str[i] && is_in_set(str[i], " \t\n"))
		i++;
	while (str[i] && !is_in_set(str[i], " \t\n<>"))
	{
		if (is_in_set(str[i], "\"\'"))
			i += skip_quote(&str[i], str[i]);
		i++;
	}
	return (i);
}

static char	*str_without_redir(char *str, char *cmd, int redirs_size)
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
			j += go_to_next_redir_it(&cmd[i + j]);
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
			j = go_to_next_redir_it(str);
			str += j;
			redirs_size += j;
		}
		if (*str && !is_in_set(*str, "<>"))
			str++;
	}
	str = str_without_redir(str, cmd->cmd, redirs_size);
	return (str);
}
