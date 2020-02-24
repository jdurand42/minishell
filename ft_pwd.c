/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:18:28 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/17 11:35:42 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char *b;

	b = NULL;
	if (!(b = getcwd(b, 0)))
	{
		ft_printf("Malloc error\n");
		safe_exit(data);
	}
	data->buf = b;
	write_redir(data);
	free(b);
	exit(0);
}
