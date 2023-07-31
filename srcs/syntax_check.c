/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:29:57 by jfarkas           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/01 00:47:54 by jfarkas          ###   ########.fr       */
=======
/*   Updated: 2023/08/01 00:38:31 by jfarkas          ###   ########.fr       */
>>>>>>> ddea1d7 (ambiguous redirects)
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_empty(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (!is_in_set(cmd_line[i], " \t\n"))
			return (0);
		i++;
	}
	return (1);
}

/*Return string without first found token*/
char	*get_token(char *cmd_line, char **token)
{
	int		i;
	int		j;

	i = 0;
	while(cmd_line[i])
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
	while(str[i])
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

int	check_next_token(char *cmd_line, char **syntax_error)
{
	char	**token;
	char	*str;
	int		i;

	i = 1;
	token = ft_split("<<:>>:<:>:|",':');
	str = get_token(cmd_line, token);
	if (!str)
	{
		free_array(token);
		return (0);
	}
	while (is_in_set(str[i], " \t\n"))
		i++;
	if (str[0] == '|' && str[i] == '|')
	{
		*syntax_error = "|";
		free_array(token);
		return (1);
	}
	if (is_in_set(str[0], "<>") && is_in_set(str[i], "<>"))
	{
		*syntax_error = ft_strdup(is_token(&str[i], token));
		free_array(token);
		return (1);
	}
	free_array(token);
	return (0);
}

int	check_single_quote(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (is_in_set(cmd_line[i], "\'\""))
		{
			if (!is_paired(&cmd_line[i], cmd_line[i]))
				return (1);
			i += skip_quote(&cmd_line[i], cmd_line[i]);
		}
		i++;
	}
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
	while ((error = check_next_token(&cmd_line[i], &syntax_error)) == 0)
	{
		if (!cmd_line[i])
			break;
		if (is_in_set(cmd_line[i], "\'\""))
			i += skip_quote(&cmd_line[i], cmd_line[i]);
		i++;
	}
	if (error)
	{
		printf_fd(2, "bash: syntax error near unexpected token `%s'\n", syntax_error);
		EXIT_CODE = 2;
	}
	free(syntax_error);
	return (error);
}
