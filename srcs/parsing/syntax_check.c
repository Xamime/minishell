/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:29:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/07 17:29:22 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Return string with first found token*/
static char	*get_token(char *cmd_line, char **token)
{
	int		i;
	int		j;

	i = 0;
	while (cmd_line[i])
	{
		j = 0;
		if (is_in_set(cmd_line[i], "\'\""))
			i += skip_quote(&cmd_line[i], cmd_line[i]);
		while (token[j])
		{
			if (cmd_line[i] == token[j][0]
				&& cmd_line[i + 1] && cmd_line[i + 1] == token[j][1])
				return (&cmd_line[i + 1]);
			if (cmd_line[i] == token[j][0])
				return (&cmd_line[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

static char	*is_token(char *str, char **token)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (token[j])
		{
			if (str[i] == token[j][0]
				&& str[i + 1] && str[i + 1] == token[j][1])
				return (token[j]);
			if (str[i] == token[j][0] && !token[j][1])
				return (token[j]);
			j++;
		}
		i++;
	}
	return (NULL);
}

static int	ft_error(char *str, char **token, char **syntax_error)
{
	int	i;

	i = 1;
	while (is_in_set(str[i], " \t\n"))
		i++;
	if (is_token(&str[0], token) && (!str[i] || str[i] == '|'))
	{
		if (!str[i])
			*syntax_error = ft_strdup("newline");
		else
			*syntax_error = ft_strdup("|");
		free_array(token);
		return (1);
	}
	if (is_in_set(str[0], "<>") && is_in_set(str[i], "<>"))
	{
		*syntax_error = ft_strdup(is_token(&str[i], token));
		free_array(token);
		return (1);
	}
	return (0);
}

static int	check_next_token(char *cmd_line, char **syntax_error)
{
	char	**token;
	char	*str;

	token = ft_split("<<:>>:<:>:|", ':');
	str = get_token(cmd_line, token);
	if (!str)
	{
		free_array(token);
		return (0);
	}
	if (ft_error(str, token, syntax_error))
		return (1);
	free_array(token);
	return (0);
}

/*Return 1 if there is syntax error */
int	syntax_errors(char *cmd_line)
{
	int		i;
	int		error;
	char	*syntax_error;

	i = 0;
	error = 0;
	if (is_empty(cmd_line))
		return (-1);
	if (check_single_quote(cmd_line))
		return (2);
	if (cmd_line[0] == '|')
	{
		syntax_error = ft_strdup("|");
		error = 2;
	}
	while (error == 0)
	{
		error = check_next_token(&cmd_line[i], &syntax_error);
		if (!cmd_line[i])
			break ;
		if (is_in_set(cmd_line[i], "\'\""))
			i += skip_quote(&cmd_line[i], cmd_line[i]);
		i++;
	}
	print_syntax_error(error, syntax_error);
	return (error);
}
