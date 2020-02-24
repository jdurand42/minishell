/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:20:31 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/14 19:24:58 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ms	*get_buffer_utils(t_ms *lst)
{
	lst = lst->next;
	if (lst != NULL)
		lst = lst->next;
	return (lst);
}

char		*get_buffer(t_data *data, t_ms *lst)
{
	int		j;
	char	*b;

	j = 0;
	b = ft_strdup("");
	while (lst != NULL)
	{
		if ((!ft_strncmp(lst->content, ">", 1) ||
		!ft_strncmp(lst->content, "<", 1)) && lst->sep == 0)
		{
			lst = get_buffer_utils(lst);
			continue ;
		}
		if (lst->content != NULL)
		{
			b = ft_strjoin_1(b, ft_write_args(data, lst->content, lst->sep));
			if (lst->space == 1 && lst->next != NULL &&
			ft_strncmp(ft_write_args(data, lst->next->content,
			lst->next->sep), "", 1) && ft_strncmp(ft_write_args(data,
			lst->content, lst->sep), "", 1))
				b = ft_strjoin_1(b, " ");
		}
		lst = lst->next;
	}
	return (add_garbage_ret(data, (void**)&b));
}
