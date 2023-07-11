/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:07:14 by mdesrose          #+#    #+#             */
/*   Updated: 2023/07/11 16:02:15 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

extern int	EXIT_CODE;

typedef struct s_redir
{
	t_list	*infiles;
	t_list	*heredocs;
	t_list	*outfiles;
}	t_redir;

typedef struct s_cmd
{
	char	*cmd_name;
	char	*cmd;
	char	**words;
	char	**path;
	int		infile;
	int		outfile;
	t_redir	*redirs;
}				t_cmd;

typedef struct s_expv
{
	void	*next;
	char	*name;
	char	*var;
}				t_expv;

typedef struct s_data
{
	void	*next;
	t_expv	*export;
}				t_data;

typedef struct s_expansion
{
	char	*name;
	char	*var;
	int		in_double;
	int		found_dollar;
	int		mode;
}	t_expansion;

void	freelist(t_expv *export);
char	**ft_split_quotes(char *s, char c);

/////////////////////////////////////////////////////
///					expand.c					  ///
/////////////////////////////////////////////////////

char	*set_without_quotes(char *str);
char	*make_dollars(char *str, t_data *data, int mode);

/////////////////////////////////////////////////////
///					parsing2.c					  ///
/////////////////////////////////////////////////////

char	*get_access(t_cmd *cmd, t_data *data);
int		is_builtin(char *cmd);

/////////////////////////////////////////////////////
///					utils2.c					  ///
/////////////////////////////////////////////////////

char	*get_filename(char *str);
void	better_lstclear(t_list *lst);
char	*get_path(t_data *data);
void	free_redirects(t_redir *redirs);
void	close_fds(t_list *lst);

/////////////////////////////////////////////////////
///					redirs.c					  ///
/////////////////////////////////////////////////////

int		secure_open(char *mode, char *filename);
int		heredoc_name(t_cmd cmds, char *filename);
int		parse_redir(char *str, t_redir **redirs, t_cmd *cmd);

/////////////////////////////////////////////////////
///					redirs_utils.c				  ///
/////////////////////////////////////////////////////

void	set_heredocs(t_cmd *cmds);
void	check_redirect(t_list *infile, t_cmd *cmd, t_list *heredoc);
void	make_list(t_cmd *cmds, int *fd);
void	open_last_file(char *type, int *fd, char *filename, t_redir *redirs);
char	*remove_redir(t_cmd	*cmd, t_data *data);
char	*str_without_redir(char *str, char* cmd, int redirs_size);

/////////////////////////////////////////////////////
///					expand2.c					  ///
/////////////////////////////////////////////////////

char	*new_string(t_expansion *exp, char *str);
char	*set_new_str(t_expansion *exp, char *str);
void	set_double_quotes(t_expansion *exp);
void	add_var_value(t_expansion *exp, char *new_str, int *i, int *j);
int		skip_and_copy(char *str, char *new_str, char c, int *j);

/////////////////////////////////////////////////////
///					split_quotes_utils.c		  ///
/////////////////////////////////////////////////////

int		nbwords(char *s, char c);
int		is_in_set(char c, char *set);
int		is_paired(char *str, char quote);
char	*skip_to_char(char *str, char c);

/////////////////////////////////////////////////////
///					parsing.c					  ///
/////////////////////////////////////////////////////

int		parse_cmd(t_cmd *cmd, t_data *data);
void	replace_address(char **addr1, char *addr2);
void	split_pipe(t_data *data, t_cmd *cmds);

/////////////////////////////////////////////////////
///					init.c						  ///
/////////////////////////////////////////////////////

void	init_heredoc(t_cmd *cmds);
t_expv	**init_env(char **expv);
void	init_redir(t_redir **redirs);
t_cmd	*init_cmds(char *cmd_line);

/////////////////////////////////////////////////////
///					builtins.c					  ///
/////////////////////////////////////////////////////

void	exec_builtin(t_cmd cmd, t_data *data);

/////////////////////////////////////////////////////
///					export.c					  ///
/////////////////////////////////////////////////////

void	export(t_cmd cmd, t_data *data);

/////////////////////////////////////////////////////
///					export_utils.c				  ///
/////////////////////////////////////////////////////

void	print_export_var(char *name, char *var);
t_expv	*find_min_ascii(t_expv *export, t_expv *sorted);
void	set_var_line(char *line, char **name, char **var);
void	change_var(t_data **data, char *name, char *var, int mode);
int		check_forbidden_caracter(char *str);

/////////////////////////////////////////////////////
///					utils1.c					  ///
/////////////////////////////////////////////////////

void	remove_last_nl(char *str);
int		is_in(t_expv *list, char *str);
int		ft_strchrlen(char *str, char c);
int		check_plus_one(char c);
void	free_array(char **array);

/////////////////////////////////////////////////////
///					unset.c						  ///
/////////////////////////////////////////////////////

void	unset(t_cmd cmd, t_data *data);

/////////////////////////////////////////////////////
///				export_list_utils.c				  ///
/////////////////////////////////////////////////////

void	del_one(t_expv *list, t_expv *to_del);
t_expv	*ft_expv_last(t_expv *expv);
t_expv	*ft_expv_new(char *var, char *name);
void	ft_expv_add_back(t_expv **expv, t_expv *new);
int		ft_expv_size(t_expv *expv);

char	*ft_getenv(char *str, t_data *data);
void	update_pwd(t_data *data, char *oldpwd);

#endif