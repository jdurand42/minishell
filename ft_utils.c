/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:53:37 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/17 17:19:04 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->n_cmds = 0;
	data->i = 0;
	data->cmds = NULL;
	free(data->sep);
	data->sep = NULL;
	data->lst = NULL;
	data->buf = NULL;
	data->code = 0;
	ft_memset(data->pipe, 0, sizeof(data->pipe));
	data->cmd_pipe = 0;
	data->pipes = NULL;
	data->tab_path = NULL;
	data->cmds_pipe = NULL;
	data->args_pipe = NULL;
	data->split_pipe = NULL;
	data->first = 1;
	data->flux->redir = 'z';
	free(data->entry);
	data->entry = NULL;
	data->option_n = 0;
	data->gb_collector2 = NULL;
}

int		is_sep(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	else
		return (0);
}

void	ft_free_lst(t_ms **lst)
{
	int i;

	i = 0;
	while (lst[i] != 0)
	{
		ft_lstclear_ms(&lst[i], free);
		i++;
	}
	free(lst[i]);
	free(lst);
}

int		ft_envsize(t_env *env)
{
	int size;

	size = 0;
	while (env)
	{
		if (env->exp == 1)
			size += 1;
		env = env->next;
	}
	return (size);
}

int		check_if_args(t_ms *lst)
{
	if (lst && lst->next == NULL)
		return (0);
	if (!ft_strncmp(lst->next->content, ">", 2) ||
	!ft_strncmp(lst->next->content, "<", 2)
	|| !ft_strncmp(lst->next->content, ">>", 3))
		return (0);
	return (1);
}
