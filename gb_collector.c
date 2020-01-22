/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 19:02:58 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/22 19:50:21 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear2(t_list **lst, void (*del)(void*))
{
	t_list	*buffer;
	t_list	*buffernext;

	if (!(*del))
		return ;
	if (lst == NULL)
		return ;
	buffer = *lst;
	while (buffer != NULL && buffernext != NULL)
	{
		printf("here\n");
		buffernext = buffer->next;
		printf("%p\n", buffer->next);

		del(buffer->content);
		//free(buffer);
		buffer = buffernext;
	}
	*lst = NULL;
}

void	*safe_malloc(size_t n, size_t n_size, t_data *data)
{
	void *b;

	if (!(b = malloc(n * n_size)))
		return NULL;
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
	//ft_lstclear2(&data->gb_collector, free);
	t_list *b_next;

	while (data->gb_collector != NULL)
	{
		b_next = data->gb_collector->next;
		free(data->gb_collector->content);
		free(data->gb_collector);
		data->gb_collector = b_next;
	}
	/*while (data->gb_collector != NULL)
		b = data->gb_collector;
		free(b->content);
		data->gb_collector = data->gb_collector->next;
		free(b);*/

}
