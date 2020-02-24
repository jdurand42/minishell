/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:45:58 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/14 17:04:13 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		write_redir(t_data *data)
{
	t_flux *begin_flux;

	begin_flux = data->flux;
	while (data->flux != 0)
	{
		if (!data->option_n)
			ft_dprintf(1, "%s\n", data->buf);
		else
			ft_dprintf(1, "%s", data->buf);
		if (data->flux->next != NULL)
			data->flux = data->flux->next;
		else
			break ;
	}
	data->flux = begin_flux;
	return (1);
}
