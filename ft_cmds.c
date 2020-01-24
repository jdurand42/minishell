/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:44:37 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/24 11:02:07 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_echo(t_data *data, t_list *lst)
{
	int		j;

	j = 0;
	printf("au moins on est ici\n");
	lst = lst->next;
	while (lst != 0)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}
