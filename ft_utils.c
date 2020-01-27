/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:41:22 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/27 13:25:18 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void 	init_data(t_data *data, char **envp)
{
	data->n_cmds = 0;
	data->i = 0;
	data->cmds = NULL;
	data->sep = NULL;
	data->lst = NULL;
	data->flux = 0;
	data->envp = envp;
}

int		is_sep(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	else
		return (0);
}

void 	ft_free_lst(t_data *data, t_list **lst)
{
	int i;

	i = 0;
	while (i <= data->n_cmds)
	{
		ft_lstclear(&lst[i], free);
		i++;
	}
	//free(lst);
}
