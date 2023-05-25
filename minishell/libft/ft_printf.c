/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:07:50 by mdesrose          #+#    #+#             */
/*   Updated: 2022/10/05 16:33:46 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	ft_loop(const char *s, va_list *args, int *count)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '%')
		{
			write(1, &s[i], 1);
			(*count)++;
		}
		if (s[i] == '%')
		{
			ft_check(s[i + 1], args, count);
			i++;
		}
		i++;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		*ptr;

	if (!str)
		return (-1);
	count = 0;
	ptr = &count;
	va_start(args, str);
	ft_loop(str, &args, ptr);
	va_end(args);
	return (count);
}
