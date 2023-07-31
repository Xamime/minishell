/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:07:50 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/31 22:57:34 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_loop(int fd, const char *s, va_list *args, int *count)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '%')
		{
			write(fd, &s[i], 1);
			(*count)++;
		}
		if (s[i] == '%')
		{
			ft_check(fd, s[i + 1], args, count);
			i++;
		}
		i++;
	}
}

int	printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		count;
	int		*ptr;

	if (!str)
		return (-1);
	count = 0;
	ptr = &count;
	va_start(args, str);
	ft_loop(fd, str, &args, ptr);
	va_end(args);
	return (count);
}
