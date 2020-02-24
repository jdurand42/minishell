/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:44:37 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/14 16:36:26 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_fill_env(t_data *data)
{
	char	*str;
	char	*tmp;

	str = ft_strjoin(data->lst_env->name, "=");
	tmp = ft_strjoin(str, data->lst_env->value);
	if (data->lst_env->next)
		data->buf = ft_strjoin(tmp, " ");
	else
		data->buf = ft_strdup(tmp);
	free(str);
	free(tmp);
	write_redir(data);
	free(data->buf);
	data->buf = NULL;
	if (data->flux->redir == 'w')
		data->flux->redir = 'a';
	return (0);
}

void	ft_env(t_data *data, t_ms *lst)
{
	t_env	*begin;
	t_flux	*begin_flux;

	if (lst->next != NULL && ft_strncmp(lst->next->content, ">", 1))
		ft_printf("env: too many arguments\n");
	else
	{
		begin = data->lst_env;
		begin_flux = data->flux;
		if (data->flux->next)
			data->flux = data->flux->next;
		while (data->lst_env != NULL)
		{
			if (data->lst_env->exp == 1)
				ft_fill_env(data);
			data->lst_env = data->lst_env->next;
		}
		data->lst_env = begin;
		data->flux = begin_flux;
	}
	exit(0);
}
