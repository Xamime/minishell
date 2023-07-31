/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:46:33 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/31 22:32:55 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*get_filename(char *str, t_expv *expv)
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
			size += skip_quote(&str[size], str[size]);
		else
			size++;
	}
	filename = ft_substr(str, 0, size);
	// check_ambiguous redirect
	replace_address(&filename, make_dollars(filename, expv, 0));
	replace_address(&filename, make_dollars(filename, expv, 1));
	replace_address(&filename, set_without_quotes(filename));
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

void	unlink_heredocs(t_list *lst)
{
	t_list	*ptr;

	ptr = lst;
	while (ptr)
	{
		unlink((char *)ptr->content);
		ptr = ptr->next;
	}
}

void	close_next_cmds_fds(t_cmd *cmds)
{
	int	i;

	i = 1;
	while (cmds[i].cmd)
	{
		if (cmds[i].infile > -1)
			close(cmds[i].infile);
		if (cmds[i].outfile > -1)
			close(cmds[i].outfile);
		i++;
	}
}
