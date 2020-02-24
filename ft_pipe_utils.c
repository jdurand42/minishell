/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:41:22 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/17 17:02:58 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_data *data)
{
	data->pipes = NULL;
	data->tab_path = NULL;
	data->cmds_pipe = NULL;
	data->args_pipe = NULL;
	data->split_pipe = NULL;
	data->first = 1;
	data->flux->redir = 'z';
}

void	del_item(char ***as)
{
	if (as != NULL && *as != NULL && **as != NULL)
	{
		free(**as);
		**as = NULL;
	}
}

void	free_flux(t_data *data)
{
	t_flux *begin;
	t_flux *current;

	begin = data->flux;
	while (data->flux->next)
	{
		current = data->flux->next;
		free(data->flux->next->fichier);
		free(data->flux->next);
		data->flux->next = NULL;
		data->flux->next = current->next;
	}
	data->flux = begin;
	if (data->buf)
		free(data->buf);
	data->buf = NULL;
	if (data->pipes)
		free(data->pipes);
}

void	free_double_tab(char ***item, int i)
{
	int j;

	if (item && item[i] && *item[i])
	{
		j = 0;
		while (item[i][j])
		{
			ft_strdel(&item[i][j]);
			j++;
		}
		free(item[i][j]);
		free(item[i]);
		item[i] = NULL;
	}
}

void	free_pipe_cmd(t_data *data)
{
	int i;

	i = 0;
	while (i < data->pipe[data->cmd_pipe] + 1)
	{
		free_double_tab(data->split_pipe, i);
		ft_strdel(&data->cmds_pipe[i]);
		if (data->pipes)
		{
			if (data->pipes[i])
			{
				free(data->pipes[i]);
				data->pipes[i] = NULL;
			}
		}
		free_double_tab(data->tab_path, i);
		i++;
	}
	if (data->cmds_pipe)
		free(data->cmds_pipe);
	if (data->tab_path)
		free(data->tab_path);
	if (data->split_pipe)
		free(data->split_pipe);
	free_flux(data);
}
