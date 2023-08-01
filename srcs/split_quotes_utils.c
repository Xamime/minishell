/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:37:21 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/01 22:30:36 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Return True if in set
int	is_in_set(char c, char *set)
{
	if (!c)
		return (0);
	while (*set && *set != c)
		set++;
	if (*set)
		return (1);
	return (0);
}

int	is_paired(char *str, char quote)
{
	str++;
	while (*str && *str != quote)
		str++;
	if (*str)
		return (1);
	return (0);
}

char	*skip_to_char(char *str, char c)
{
	str++;
	while (*str && *str != c)
		str++;
	return (str);
}

int	skip_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}
