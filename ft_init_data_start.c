/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:52:14 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/17 17:07:42 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_exit(t_data *data)
{
	ft_printf("%s\n", "malloc error");
	safe_exit(data);
	exit(0);
}

void	init_data_start(t_data *data, char **envp, int argc, char **av)
{
	data->n_cmds = 0;
	argc = 1;
	av[0] = "";
	data->gb_collector2 = NULL;
	data->i = 0;
	data->cmds = NULL;
	data->sep = NULL;
	data->lst = NULL;
	data->buf = NULL;
	data->envp = envp;
	data->lst_env = init_env(envp);
	if (!(data->flux = (t_flux *)malloc(sizeof(t_flux))))
		print_exit(data);
	data->code = 0;
	data->flux->fd = 1;
	data->first = 1;
	data->flux->redir = 'z';
	data->split_pipe = NULL;
	data->tab_path = NULL;
	data->cmd_pipe = 0;
	data->cmds_pipe = NULL;
	if (!(data->pipe = (int *)malloc(sizeof(int) * 100)))
		print_exit(data);
	data->option_n = 0;
}
