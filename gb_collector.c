/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 19:02:58 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/23 17:59:38 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(size_t n, size_t n_size, t_data *data)
{
	void *b;

	if (!(b = malloc(n * n_size)))
		safe_exit(data);
	ft_bzero(b, n * n_size);
	ft_lstadd_front(&data->gb_collector, ft_lstnew(b));
//	printf("%p\n", data->gb_collector->content);
	return b;
}

void 	safe_exit(t_data *data)
{
	void *b;

	if (!data->gb_collector)
		return ;
	t_list *b_next;
//	ft_lstclear(&data->gb_collector, free);

	while (data->gb_collector != NULL)
	{
		b_next = data->gb_collector->next;
		free(data->gb_collector->content);
		free(data->gb_collector);
		data->gb_collector = b_next;
	}
	while(1);
	exit(0);
}
