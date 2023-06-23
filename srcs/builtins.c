/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:06:33 by mdesrose          #+#    #+#             */
/*   Updated: 2023/05/26 11:12:41 by mdesrose         ###   ########.fr       */
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

void	cd(char *cmd, t_data *data)
{
	char	*home;
	char	*oldpwd;

	home = ft_getenv("HOME", data);
	oldpwd = malloc(sizeof(char) * 4096);
	oldpwd = getcwd(oldpwd, 4096); // a changer
	if (cmd == NULL)
	{
		if (home)
		{
			chdir(home);// a voir
			update_pwd(data, oldpwd);
		}
		else
			printf("cd: HOME not set\n");
		return ;
	}
	remove_last_nl(cmd);
	if (chdir(cmd) == -1)
		ft_printf("no dir\n");
	else
		update_pwd(data, oldpwd);
	free(oldpwd); // a tcheck
}

void	echo(t_cmd cmd)
{
	int	i;

	i = 1;
	if (!cmd.words[1])
	{
		printf("\n");
		return ;
	}
	if (!ft_strcmp(cmd.words[1], "-n"))
		i = 2;
	while (cmd.words[i])
	{
		ft_printf("%s", cmd.words[i]);
		if (cmd.words[i + 1])
			ft_printf(" ");
		i++;
	}
	if (ft_strncmp(cmd.words[1], "-n", 2))
		ft_printf("\n");
}

void	print_env(t_data *data)
{
	t_expv	*tmp;

	tmp = data->export;
	while (tmp)
	{
		if (tmp->var)
			ft_printf("%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
}

void	exec_builtin(t_cmd cmd, t_data *data)
{
	if (!ft_strcmp(cmd.cmd_name, "pwd"))
		pwd();
	else if (!ft_strcmp(cmd.cmd_name, "cd"))
		cd(cmd.words[1], data);
	else if (!ft_strcmp(cmd.cmd_name, "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd.cmd_name, "exit"))
	{
		freelist(data->export);
		exit(0);
	}
	else if (!ft_strcmp(cmd.cmd_name, "env"))
		print_env(data);
	else if (!ft_strcmp(cmd.cmd_name, "export"))
		export(cmd, data);
	else if (!ft_strcmp(cmd.cmd_name, "unset"))
		unset(cmd, data);
}
