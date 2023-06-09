/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:04:49 by mdesrose          #+#    #+#             */
/*   Updated: 2022/09/26 13:51:15 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (c > '`' && c < '{')
		return (8);
	else if (c > '/' && c < ':')
		return (8);
	else if (c > '@' && c < '[')
		return (8);
	return (0);
}
