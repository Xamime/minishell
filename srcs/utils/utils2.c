/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:46:33 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/05 19:06:49 by jfarkas          ###   ########.fr       */
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

void	get_sep_nb(char *filename, int *before, int *after, t_expv *expv)
{
	int		i;
	char	*new_str;

	i = 0;
	while (filename && filename[i])
	{
		if (is_in_set(filename[i], " \t\n"))
			(*before)++;
		i++;
	}
	new_str = make_dollars(filename, expv, 0);
	i = 0;
	while (new_str && new_str[i])
	{
		if (is_in_set(new_str[i], " \t\n"))
			(*after)++;
		i++;
	}
	free(new_str);
}

int	check_ambiguous_redirect(char *filename, t_expv *expv)
{
	int		before_sep_nb;
	int		after_sep_nb;

	before_sep_nb = 0;
	after_sep_nb = 0;
	get_sep_nb(filename, &before_sep_nb, &after_sep_nb, expv);
	if (before_sep_nb < after_sep_nb)
	{
		printf_fd(2, "minishell: %s: ambiguous redirect\n", filename);
		free(filename);
		return (1);
	}
	return (0);
}

char	*get_filename(char *str, t_expv *expv, t_cmd *cmd)
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
			size += skip_quote(&str[size], str[size]) + 1;
		else
			size++;
	}
	filename = ft_substr(str, 0, size);
	if (check_ambiguous_redirect(filename, expv))
	{
		cmd->status = 1;
		return (NULL);
	}
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
