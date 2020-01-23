/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:41:22 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/23 18:03:47 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void 	init_data(t_data *data)
{
	data->n_cmds = 0;
	data->i = 0;
	data->cmds = NULL;
	data->sep = NULL;
}

int		is_sep(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	else
		return (0);
}
