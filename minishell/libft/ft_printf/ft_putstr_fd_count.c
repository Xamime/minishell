/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:24:32 by mdesrose          #+#    #+#             */
/*   Updated: 2022/10/01 17:36:12 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putstr_fd_count(char *s, int fd, int *count)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		*count += write(1, "(null)", 6);
		return ;
	}
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
		(*count)++;
	}
}
