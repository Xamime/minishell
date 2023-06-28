/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:46:33 by mdesrose          #+#    #+#             */
/*   Updated: 2023/06/28 16:41:29 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_filename(char *str)
{
	int		size;
	char	*filename;

	printf("get filename, str = %s\n", str);
	while (is_in_set(*str, "<>"))
		str++;
	while (is_in_set(*str, " \t\n"))
		str++;
	size = 0;
	while (str[size] && !is_in_set(str[size], " \t\n<>"))
		size++;
	filename = ft_substr(str, 0, size);
	printf("get filename, filename = %s\n", filename);
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
