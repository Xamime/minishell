/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:29:57 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/31 02:56:20 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_redir2(char *cmd_line)
{
	int	i;
	int tru;

	tru = 0;
	i = 0;
	while (cmd_line && cmd_line[i])
	{
		while (is_in_set(cmd_line[i], "<>"))
		{
			tru = 1;
			i++;
		}
		while (cmd_line[i] == ' ')
			i++;
		if (tru && is_in_set(cmd_line[i], "<>"))
			return (1);
		i++;
	}
	return (0);
}

int	syntax_redir(char *cmd_line)
{
	int	i;

	i = 0;
	//if (is_in_set(cmd_line[0], "<>"))

	while (cmd_line && cmd_line[i])
	{
		if (is_in_set(cmd_line[i], "<>") && is_in_set(cmd_line[i + 1], "<>")
		&& is_in_set(cmd_line[i + 2], "<>"))
			return (1);
		if (is_in_set(cmd_line[i], "<>") && is_in_set(cmd_line[i + 1], "<>"))
		{
			i += 2;
			while (cmd_line[i] == ' ')
				i++;
		}
		if (!cmd_line[i] || is_in_set(cmd_line[i], "\n\0") )//|| syntax_redir2(cmd_line))
			return (1);
		i++;
	}
	return (0);
}

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
				return (&cmd_line[i + 2]);
			if (cmd_line[i] == token[j][0])
				return (&cmd_line[i + 1]);
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

int	check_next_token(char *cmd_line)
{
	char	**token;
	char	*str;
	char	*syntax_error;
	int		i;

	i = 0;
	token = ft_split("<<:>>:<:>:|",':');
	str = get_token(cmd_line, token);
	if (!str)
		return (-1);
	while (is_in_set(str[i], " \t\n"))
		i++;
	if (is_in_set(str[i], "<>|"))
	{
		syntax_error = is_token(&str[i], token);
		printf("syn_err = %s\n",syntax_error);
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
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (is_empty(cmd_line))
		return (-1);
	// if (check_single_quote(cmd_line))
	// 	return (1);
	// while (check_next_token(&cmd_line[i]) == 0)
	// {
	// 	if (!cmd_line[i])
	// 		break;
	// 	i++;
	// }
	// error = syntax_redir(cmd_line);
	// if (error && !is_in_set(cmd_line[0], "&|);"))
	// 	error = 1;
	// // while(cmd_line && cmd_line[i])
	// // {
	// // 	if (!error && !is_in_set(cmd_line[i], " \t\n"))
	// // 		error = 1;
	// // 	i++;
	// // }
	if (error)
		EXIT_CODE = 2;
	return (error);
}
