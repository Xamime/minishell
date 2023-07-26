/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:06:33 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/25 22:53:10 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	*dir;
	char	*buf;
	int		size;

	size = 50;
	dir = NULL;
	buf = NULL;
	while (dir == NULL)
	{
		if (buf)
			free(buf);
		buf = malloc(sizeof(char) * size);
		dir = getcwd(buf, size);
		size += 50;
	}
	ft_printf("%s\n", dir);
	free(dir);
	free(buf); // a tcheck
}

void	cd(char *cmd, t_expv *expv)
{
	char	*home;
	char	*oldpwd;

	home = ft_getenv("HOME", expv);
	oldpwd = malloc(sizeof(char) * 4096);
	oldpwd = getcwd(oldpwd, 4096); // a changer
	if (cmd == NULL)
	{
		if (home)
		{
			chdir(home);// a voir
			update_pwd(expv, oldpwd);
		}
		else
			printf("cd: HOME not set\n");
		return ;
	}
	remove_last_nl(cmd);
	if (chdir(cmd) == -1)
		ft_printf("no dir\n");
	else
		update_pwd(expv, oldpwd);
	free(oldpwd); // a tcheck
}

int	check_n(t_cmd *cmd, int i)
{
	int	j;

	j = 1;
	if (ft_strncmp(cmd->words[i], "-n", 2))
		return (0);
	while (cmd->words[i][j])
	{
		if (cmd->words[i][j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	echo(t_cmd *cmd)
{
	int	i;
	int	j;

	j = 1;
	i = 1;
	if (!cmd->words[1])
	{
		printf("\n");
		return ;
	}
	while (cmd->words[i])
	{
		if (check_n(cmd, i))
			j++;
		else
			break;
		i++;
	}
	i = j;
	while (cmd->words[j])
	{
		ft_printf("%s", cmd->words[j]);
		if (cmd->words[j + 1])
			ft_printf(" ");
		j++;
	}
	if (i < 2)
		ft_printf("\n");
}

void	print_env(t_expv *expv)
{
	t_expv	*tmp;

	tmp = expv;
	while (tmp)
	{
		if (tmp->var)
			ft_printf("%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
}

void	exec_builtin(t_cmd *cmd, t_expv *expv)
{
	if (!ft_strcmp(cmd->cmd_name, "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->cmd_name, "cd"))
		cd(cmd->words[1], expv);
	else if (!ft_strcmp(cmd->cmd_name, "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd->cmd_name, "exit")) // a changer
	{
		freelist(expv);
		exit(0);
	}
	else if (!ft_strcmp(cmd->cmd_name, "env"))
		print_env(expv);
	else if (!ft_strcmp(cmd->cmd_name, "export"))
		export(cmd, &expv);
	else if (!ft_strcmp(cmd->cmd_name, "unset"))
		unset(cmd, &expv);
}
