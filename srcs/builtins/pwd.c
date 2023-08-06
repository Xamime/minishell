/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:36:44 by jfarkas           #+#    #+#             */
/*   Updated: 2023/08/06 22:56:04 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(void)
{
	char	*dir;

	dir = get_cwd_name();
	if (!dir)
		printf("minishell: pwd: %s\n", strerror(116));
	else
		printf("%s\n", dir);
	free(dir);
}
