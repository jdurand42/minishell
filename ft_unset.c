/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:44:37 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/14 18:29:14 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset_var(t_env *lst_env, int option)
{
	free(lst_env->name);
	free(lst_env->value);
	lst_env->name = NULL;
	lst_env->value = NULL;
	lst_env->exp = 0;
	if (option == 1)
		free(lst_env);
	return (0);
}

void	ft_unset_boucle(t_data **data, char *args)
{
	while ((*data)->lst_env && (*data)->lst_env->next)
	{
		if (ft_strncmp(args, (*data)->lst_env->next->name,
			ft_strlen(args)) == 0)
		{
			ft_unset_var((*data)->lst_env->next, 2);
			free((*data)->lst_env->next);
			(*data)->lst_env->next = (*data)->lst_env->next->next;
		}
		(*data)->lst_env = (*data)->lst_env->next;
	}
}

void	ft_unset(t_data **data, t_ms *lst)
{
	t_env	*begin;
	char	*args;

	args = NULL;
	begin = (*data)->lst_env;
	if (!lst->next)
		return ;
	while ((lst = lst->next))
	{
		if ((*data)->lst_env)
		{
			args = ft_strdup(ft_write_args(*data, lst->content, 1));
			if (ft_strncmp(args, (*data)->lst_env->name, ft_strlen(args)) == 0)
			{
				begin = (*data)->lst_env->next;
				ft_unset_var((*data)->lst_env, 1);
			}
		}
		ft_unset_boucle(data, args);
		free(args);
		(*data)->lst_env = begin;
	}
	(*data)->buf = ft_strdup("");
	(*data)->option_n = 1;
	write_redir((*data));
}
