/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:29:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/01 22:53:02 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Return string with first found token*/
char	*get_token(char *cmd_line, char **token)
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
			if (cmd_line[i] == token[j][0] && cmd_line[i + 1] == token[j][1])
				return (&cmd_line[i + 1]);
			if (cmd_line[i] == token[j][0])
				return (&cmd_line[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*is_token(char *str, char **token)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (token[j])
		{
			if (str[i] == token[j][0] && str[i + 1] == token[j][1])
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
	if (str[0] == '|' && str[i] == '|')
	{
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

int	check_next_token(char *cmd_line, char **syntax_error)
{
	char	**token;
	char	*str;
	int		i;

	i = 1;
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
		return (1);
	while (error == 0)
	{
		error = check_next_token(&cmd_line[i], &syntax_error);
		if (!cmd_line[i])
			break ;
		if (is_in_set(cmd_line[i], "\'\""))
			i += skip_quote(&cmd_line[i], cmd_line[i]);
		i++;
	}
	syntaxe_errors2(error, syntax_error);
	return (error);
}
