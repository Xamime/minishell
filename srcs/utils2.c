/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:46:33 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/22 16:29:09 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->next && tmp->content && *(int *)tmp->content > 0)
			close(*(int *)tmp->content);
		tmp = tmp->next;
	}
}

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

void	unlink_heredocs(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].cmd)
	{
		unlink(cmds[i].heredoc_name);
		free(cmds[i].heredoc_name);
		i++;
	}
}

char	*get_path(t_data *data)
{
	t_expv	*tmp;

	tmp = data->export;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
			break ;
		tmp = tmp->next;
	}
	return (tmp->var);
}
