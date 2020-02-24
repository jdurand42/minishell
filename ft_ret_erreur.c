/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ret_erreur.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:07:18 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/18 19:56:36 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ret_erreur(t_data *data, int j)
{
	t_env	*begin;

	begin = data->lst_env;
	while (data->lst_env)
	{
		if (!ft_strncmp(data->lst_env->name, "?", 2))
		{
			free(data->lst_env->value);
			data->lst_env->value = ft_itoa(j);
		}
		data->lst_env = data->lst_env->next;
	}
	data->lst_env = begin;
}

void	msg_erreur(t_data *data)
{
	ft_ret_erreur(data, 1);
	ft_printf("%s: %s: %s:\n", data->cmds_pipe[data->nb_pipe],
	data->split_pipe[data->nb_pipe], strerror(errno));
	exit(0);
}

void	test_path(t_data *data, int i)
{
	i = 0;
	if (!ft_strncmp(data->tab_path[data->nb_pipe][i], data->cmds_pipe
		[data->nb_pipe], 3))
	{
		ft_printf("%s: no such file or directory\n",
		data->cmds_pipe[data->nb_pipe]);
		exit(127);
	}
}

void	test_path_null(t_data *data, int i)
{
	if (data->tab_path[data->nb_pipe][i] == NULL)
	{
		ft_printf("%s: command not found\n", data->cmds_pipe[data->nb_pipe]);
		exit(127);
	}
}
