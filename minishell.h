/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:59:42 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/27 13:41:43 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
//#include <fctnl.h>
#include <unistd.h>
#include "libft/libft.h"
#define PROMPT "Minishell$: "

typedef struct	s_data
{
	struct  s_list	*gb_collector;
	struct	s_list	**lst; // tableau de liste avec tous les arguments
 	char			**cmds; //tabeau de str de commandes
//	char 			**args; // plus rien
	char 			**envp; // copie du pinteur sur le tableau d'env
	char			*entry; // ce que on lit dans stdin
	char			*sep; // separateur de commandes
	int 			n_cmds; //nombre de cmds
	int				i;
	int				state; //rien
	int 			flux; // pour gerer le flux de sortie
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
t_list	*ft_lstsplit_ms(char const *s, char *set);
