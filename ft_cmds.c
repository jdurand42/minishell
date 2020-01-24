/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:44:37 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/24 10:18:27 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_echo(t_data *data, char *cmd, int i)
{
	int		j;
	char 	**args;

	j = 0;
	printf("au moins on est ici\n");
	printf("ici %s\n", &cmd[i]);
	while (cmd[i] != 0)
	{
		printf("i: %d %d\n", i, j);
		skip_spaces(&cmd[i], &i);
		j = i;
		while (cmd[j] != 0 && cmd[j] != 32)
			j++;
		ft_dprintf(1, "%.*s\n", j - i, &cmd[i]);
		i += j - i;
	}
}
