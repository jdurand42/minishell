/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 19:02:58 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/18 16:46:30 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_garbage(t_data *data, void **s)
{
	ft_lstadd_front(&data->gb_collector2, ft_lstnew(*s));
}

void		*add_garbage_ret(t_data *data, void **s)
{
	t_list *b;

	if (!(b = malloc(sizeof(t_list))))
		safe_exit(data);
	if (*s)
		b->content = *s;
	else
		b->content = NULL;
	b->next = NULL;
	if (*s)
		ft_lstadd_front(&data->gb_collector2, b);
	return (*s);
}

void		free_cmds(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i] != 0)
		free(cmds[i++]);
	free(cmds);
}

void		safe_exit(t_data *data)
{
	if (data->cmds)
		free_cmds(data->cmds);
	ft_lstclear(&data->gb_collector2, free);
	exit(0);
}
