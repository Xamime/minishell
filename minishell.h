/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:07:14 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/07 01:42:11 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

extern int	g_exit_code;

typedef struct s_redir
{
	t_list	*infiles;
	t_list	*heredocs;
	t_list	*heredoc_names;
	t_list	*outfiles;
}	t_redir;

typedef struct s_cmd
{
	char	*cmd_name;
	char	*cmd;
	char	**words;
	int		infile;
	int		outfile;
	pid_t	pid;
	int		status;
	int		error;
	int		id;
	t_redir	*redirs;
}				t_cmd;

typedef struct s_expv
{
	void	*next;
	char	*name;
	char	*var;
}				t_expv;

typedef struct s_expansion
{
	char	*name;
	char	*var;
	int		in_double;
	int		found_dollar;
	int		mode;
}	t_expansion;

/* -------------------------------------------------------------------------- */
/*                                  builtins                                  */
/* -------------------------------------------------------------------------- */

void	print_env(t_expv *expv);
void	ft_exit(char **env, t_cmd *cmds, t_expv **expv, int *real_fds);
void	export(t_cmd *cmd, t_expv **expv);
void	cd(char *directory, t_cmd *cmd, t_expv *expv);
void	echo(t_cmd *cmd);
void	pwd(void);
void	unset(t_cmd *cmd, t_expv **export);

/* ------------------------------ builtin utils ----------------------------- */

char	*get_cwd_name(void);
void	exec_builtin(t_cmd *cmd, t_expv **expv, char **env, int *real_fds);

char	*ft_getenv(char *str, t_expv *export);

/* ------------------------------ export utils ------------------------------ */

void	print_export_var(char *name, char *var);
t_expv	*find_min_ascii(t_expv *export, t_expv *sorted);
void	set_var_line(char *line, char **name, char **var);
void	change_var(t_expv *export, char *name, char *var, int mode);
int		check_forbidden_char(char *str, int entire_name);

/* ---------------------------- export list utils --------------------------- */

void	del_one(t_expv **list, t_expv *to_del);
t_expv	*ft_expv_last(t_expv *expv);
t_expv	*ft_expv_new(char *var, char *name);
void	ft_expv_add_back(t_expv **expv, t_expv *new);
int		ft_expv_size(t_expv *expv);

/* -------------------------------------------------------------------------- */
/*                                  execution                                 */
/* -------------------------------------------------------------------------- */

char	*get_access(t_cmd *cmd, t_expv *expv);
int		is_builtin(char *cmd);
void	only_one_builtin(t_expv **expv, t_cmd *cmd);
void	free_fork(t_expv *expv, t_cmd *cmds, char **env);
void	close_next_cmds_fds(t_cmd *cmds);
void	exec_cmd(t_cmd *cmds, char **env, t_expv **expv, int index);
char	**ft_get_env(t_expv *export);
void	set_pipes(int fd_in, int fd_out, int *pfd, int p_out);
int		get_exit_code(int status, t_cmd *cmd);
void	close_after_fork(t_cmd *cmds, int *pfd, int *p_out, int index);

/* -------------------------------------------------------------------------- */
/*                                redirections                                */
/* -------------------------------------------------------------------------- */

char	*get_filename(char *str, t_expv *expv, t_cmd *cmd);
void	better_lstclear(t_list *lst);
void	free_redirects(t_redir *redirs);
void	close_fds(t_list *lst);
int		secure_open(char *mode, char *filename);
int		parse_redir(char *str, t_redir **redirs, t_cmd *cmd, t_expv *expv);

int		set_heredocs(t_cmd *cmds, t_expv *expv);
char	*get_expanded_str_heredoc(char *str, t_expv *expv);
char	*get_heredoc_filename(char *str, int *exp_mode);
void	putstr_heredoc(char *tmp, int fd, int exp_mode, t_expv *expv);
int		heredoc_name(char **filename);

void	check_redirect(t_list *infile, t_cmd *cmd, t_list *heredoc);
void	open_last_file(char *type, int *fd, char *filename, t_redir *redirs);
char	*remove_redir(t_cmd	*cmd);
char	*str_without_redir(char *str, char *cmd, int redirs_size);
void	unlink_heredocs(t_list *lst);
int		check_ambiguous_redirect(char *str, t_expv *expv);
int		find_last_infile(char *str);

void	make_list(t_cmd *cmds, int *fd);

/* -------------------------------------------------------------------------- */
/*                                  expansion                                 */
/* -------------------------------------------------------------------------- */

char	*get_var_name(char *str);
char	*set_without_quotes(char *str);
char	*make_dollars(char *str, t_expv *expv, int mode);
char	*new_string(t_expansion *exp, char *str);
char	*set_new_str(t_expansion *exp, char *str);
void	add_var_value(t_expansion *exp, char *new_str, int *i, int *j);
int		skip_and_copy(char *str, char *new_str, char c, int *j);

/* -------------------------------------------------------------------------- */
/*                                   signals                                  */
/* -------------------------------------------------------------------------- */

void	sig_handler(int mode);

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

void	freelist(t_expv *expv);
int		is_in_expv(t_expv *list, char *str);
int		ft_strchrlen(char *str, char c);
void	free_array(char **array);
void	free_command(t_cmd *cmd);
void	ctrl_d(t_expv *export);

/* -------------------------------------------------------------------------- */
/*                                syntax errors                               */
/* -------------------------------------------------------------------------- */

int		check_single_quote(char *cmd_line);
void	syntaxe_errors2(int error, char *err);
int		check_next_token(char *cmd_line, char **syntax_errors);
int		syntax_errors(char *cmd_line);
int		is_empty(char *cmd_line);

/* -------------------------------------------------------------------------- */
/*                                   parsing                                  */
/* -------------------------------------------------------------------------- */

int		parse_cmd(t_cmd *cmd, t_expv *expv, int h_success);
void	replace_address(char **addr1, char *addr2);
void	split_pipe(t_expv **expv, t_cmd *cmds);

/* ---------------------------------- split --------------------------------- */

char	**ft_split_quotes(char *s, char *charset);
int		is_in_set(char c, char *set);
int		is_paired(char *str, char quote);
int		skip_quote(char *str, char quote);
char	*skip_to_char(char *str, char c);

/* -------------------------------------------------------------------------- */
/*                               initialisation                               */
/* -------------------------------------------------------------------------- */

void	init_redirs(t_cmd *cmds);
t_expv	*init_env(char **env);
t_cmd	*init_cmds(char *cmd_line);

#endif
