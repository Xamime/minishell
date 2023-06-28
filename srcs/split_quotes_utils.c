/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:37:21 by mdesrose          #+#    #+#             */
/*   Updated: 2023/06/28 17:38:46 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Return True if in set
int	is_in_set(char c, char *set)
{
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
