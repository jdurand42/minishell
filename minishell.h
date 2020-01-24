/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:59:42 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/24 13:00:58 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
//#include <fctnl.h>
#include <unistd.h>
#include "libft/libft.h"
#define PROMPT "Minishell$$$: "
/*
typedef struct	s_cmd
{
	char 	*name;
	char 	**args;
	int 	n_args;
}				t_cmd;
*/
typedef struct	s_data
{
	struct  s_list	*gb_collector;
	struct	s_list	**lst;
 	char			**cmds;
	char 			**args;
	char 			**envp;
	char			*entry;
	char			*sep;
	int 			n_cmds;
	int				i;
	int				state;
	int 			flux;
}				t_data;

void	*safe_malloc(size_t n, size_t n_size, t_data *data);
void 	safe_exit(t_data *data);
char 	*ft_strdup_skip(t_data *data, char *s);
int 	is_sep(char c);
void 	init_data(t_data *data, char **envp);
void 	parse_a_cmd(t_data *data);
void 	parse_stdin(t_data *data);
void 	parse_sep(t_data *data);
void 	exec_cmd(t_data *data, t_list *lst);
void 	ft_echo(t_data *data, t_list *lst);
void 	skip_spaces(char *s, int *i);
void 	ft_pwd(t_data *data, t_list *lst);
void 	ft_cd(t_data *data, t_list *lst);
void 	ft_env(t_data *data, t_list *lst);
void 	ft_exit(t_data *data, t_list *lst);
void 	ft_free_lst(t_data *data, t_list **lst);
