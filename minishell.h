/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:59:42 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/18 19:16:42 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include "libft/libft.h"
# define PROMPT "Minishell"
# define LIMIT_EXPORT 40

typedef struct		s_split_var
{
	int	flag;
	int	as;
	int	i;
	int	j;
	int	st;
}					t_split_var;

typedef struct		s_split_var2
{
	char	*s;
	int		cmp;
}					t_split_var2;

typedef struct		s_ms
{
	void			*content;
	int				sep;
	int				space;
	struct s_ms		*next;
}					t_ms;

typedef struct		s_env
{
	char			*name;
	char			*value;
	int				exp;
	struct s_env	*next;
}					t_env;

typedef struct		s_flux
{
	int				fd;
	char			redir;
	char			*fichier;
	struct s_flux	*next;
}					t_flux;

typedef struct		s_data
{
	struct s_list	*gb_collector2;
	struct s_ms		**lst;
	char			**cmds;
	char			**envp;
	char			**av;
	char			*entry;
	char			*sep;
	int				n_cmds;
	int				i;
	int				state;
	int				code;
	t_flux			*flux;
	t_flux			*begin_flux;
	char			*buf;
	char			***split_pipe;
	int				*pipe;
	int				**pipes;
	char			**cmds_pipe;
	char			***tab_path;
	char			***args_pipe;
	int				cmd_pipe;
	int				first;
	int				unique;
	int				last;
	int				child;
	int				redir_in;
	int				redir_out;
	int				test;
	int				nb_pipe;
	int				option_n;
	int				no_arg;
	int				nb_export;
	char			*str;
	pid_t			pid;
	t_env			*lst_env;
}					t_data;

void				*safe_malloc(size_t n, size_t n_size, t_data *data);
void				safe_exit(t_data *data);
char				*ft_strdup_skip(t_data *data, char *s);
int					is_sep(char c);
void				init_data(t_data *data);
void				init_data_start(t_data *data, char **envp, int argc, char
**av);
void				parse_a_cmd(t_data *data);
void				parse_stdin(t_data *data);
void				parse_sep(t_data *data);
void				exec_cmd(t_data *data, t_ms *lst);
void				ft_echo(t_data *data);
void				skip_spaces(char *s, int *i);
void				ft_pwd(t_data *data);
int					ft_cd(t_data *data, t_ms *lst);
void				ft_env(t_data *data, t_ms *lst);
void				ft_exit(t_data *data, t_ms *lst);
void				ft_unset(t_data **data, t_ms *lst);
void				ft_export(t_data *data, t_ms *lst);
void				ft_free_lst(t_ms **lst);
int					add_env(char **cmds, t_env *var_env);
void				ft_lstadd_back_env(t_env **alst, t_env *new);
void				ft_lstadd_back_flux(t_flux **alst, t_flux *new);
int					ft_copyuntil(char **dst, char *src, char c);
t_env				*init_env(char **envp);
int					get_env(char **cmds, t_env **var_env);
t_ms				*ft_lstsplit_ms(char *s);
int					redir(t_data *data, t_ms *lst);
void				ft_export(t_data *data, t_ms *lst);
int					write_redir(t_data *data);
char				*get_buffer(t_data *data, t_ms *lst);
char				*ft_write_args(t_data *data, char *b, int sep);
char				*get_var(t_data *data, char *b, int *inc);
char				*ft_is_exec(t_data *data, char *b, int *inc);
char				*get_var_env(t_env *env, char *name);
int					ft_check(char *str, char *valeur);
char				**ft_split_ms(char const *s, char *set, int size);
int					exec_a_cmd(t_data *data, t_ms *lst);
char				**parse_path(t_env *env);
char				**parse_av(t_data *data, t_ms *lst);
char				**parse_env(t_env *env);
int					exec_a_cmd(t_data *data, t_ms *lst);
int					ft_envsize(t_env *env);
int					ft_pipe(t_data *data, char **env, t_ms *lst);
char				**ft_fill_path(char **path, char *cmd);
int					is_add_var(t_ms **alst);
void				add_var(t_data *data, t_ms *lst);
char				*ft_parse_var_value(char *value);
int					ft_create_files(t_ms *lst);
void				ft_ret_erreur(t_data *data, int j);
char				*ft_ls(char *start, char *end);
void				ft_export_no_arg(t_data *data);
int					check_if_args(t_ms *lst);
int					test_directory(t_flux *flux, char *str);
t_ms				*ft_lstnew_ms(const void *content, char sep, int flag);
void				ft_lstclear_ms(t_ms **lst, void (*del)(void*));
int					ft_lstsize_ms(t_ms *lst);
void				ft_print_lst(t_ms *lst);
void				ft_parse_chev(t_ms *lst);
void				ft_lst_insert_one_ms(t_ms *lst, t_ms *new);
void				ft_lstadd_back_ms(t_ms **alst, t_ms *new);
void				ft_lstadd_back_ms_ls(t_ms **alst, t_ms *new);
void				ft_print_lst(t_ms *lst);
char				*ft_strjoin_1(char const *s1, char const *s2);
char				*ft_strjoin_2(char const *s1, char const *s2);
void				*add_garbage_ret(t_data *data, void **s);
void				add_garbage(t_data *data, void **s);
void				free_garbage(t_list **gb);
void				free_cmds(char **cmds);
char				*ft_strchr_set(const char *s, char *set);
int					process_pere(t_data *data, int nb_pipe, t_flux *begin);
void				init_cmd(t_data *data);
void				free_pipe_cmd(t_data *data);
int					init_data_pipe(t_data *data);
int					dup_pipe(t_data *data, int nb_pipe);
void				msg_erreur(t_data *data);
int					ft_close(t_data *data, int nb);
char				*delete_space(char *str);
int					test_builtin(t_data *data);
int					str_is_digit(t_ms *lst);
int					check_if_zero(int i);
char				*ft_do_empty_quotes(char *s);
int					check_if_last(char *s, int i);
int					ft_cmp_set_ms(char c, int *flag, t_ms *lst, int prev);
t_ms				*ft_parse_wildcard(t_ms *new, char *b);
char				*ft_write_cmd_name(char *s, t_data *data);
void				test_path(t_data *data, int i);
void				test_path_null(t_data *data, int i);

#endif
