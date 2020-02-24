/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:18:17 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/19 15:57:23 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		test_builtin(t_data *data)
{
	char *str;

	str = ft_strdup(data->cmds_pipe[data->nb_pipe]);
	if (ft_strncmp(str, "unset", 6) == 0 || ft_strncmp(str, "exit", 5) ==
		0 || ft_strncmp(str, "cd", 3) == 0 ||
		(ft_strncmp(str, "export", 7) == 0 && data->no_arg == 0))
	{
		data->buf = ft_strdup("");
		data->option_n = 1;
		free(str);
		ft_echo(data);
		return (1);
	}
	else if (ft_strncmp(data->cmds_pipe[data->nb_pipe], "echo", 5) == 0)
	{
		free(str);
		ft_echo(data);
	}
	free(str);
	return (0);
}

int		ft_close(t_data *data, int nb)
{
	close(data->pipes[nb][0]);
	close(data->pipes[nb][1]);
	return (0);
}
