/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:06:55 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/18 19:21:59 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_space(char *str)
{
	int		i;
	int		j;
	char	*s2;

	j = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i + j] && str[i + j] != ' ')
		j++;
	s2 = ft_strndup(str + i, j);
	return (s2);
}

char	**ft_fill_path(char **path, char *cmd)
{
	int		i;
	char	*b;
	char	*tmp;
	char	*commande;

	i = 0;
	while (path != 0 && path[i] != 0)
	{
		b = path[i];
		commande = delete_space(cmd);
		if (!(path[i] = ft_strjoin(path[i], commande)))
			return (NULL);
		free(b);
		free(commande);
		b = NULL;
		tmp = NULL;
		i++;
	}
	return (path);
}

int		malloc_pipe_data(t_data *data)
{
	if (!(data->pipes = (int **)malloc(sizeof(int *) * (data->pipe[data->code]
		+ 1))))
		return (0);
	if (!(data->cmds_pipe = (char **)malloc(sizeof(char *) *
		(data->pipe[data->code] + 1))))
		return (0);
	if (!(data->tab_path = (char ***)malloc(sizeof(char **) *
		(data->pipe[data->code] + 1))))
		return (0);
	if (!(data->split_pipe = (char ***)malloc(sizeof(char **) * (data->pipe
	[data->code] + 1))))
		return (0);
	return (1);
}

int		init_data_pipe(t_data *data)
{
	int		i;

	i = 0;
	if (!(malloc_pipe_data(data)))
	{
		ft_printf("Error in malloc\n");
		safe_exit(data);
	}
	while (i <= data->pipe[data->cmd_pipe])
	{
		data->split_pipe[i] = parse_av(data, data->lst[data->code + i]);
		data->cmds_pipe[i] = delete_space(data->lst[data->code + i]->content);
		if (!(data->tab_path[i] = ft_fill_path(parse_path(data->lst_env),
		data->cmds_pipe[i])))
			safe_exit(data);
		if (!(data->pipes[i] = malloc(sizeof(int) * 2)))
			safe_exit(data);
		pipe(data->pipes[i]);
		i++;
	}
	data->nb_pipe = 0;
	return (1);
}

int		dup_pipe(t_data *data, int nb_pipe)
{
	int i;

	data->unique = (data->last && data->first);
	if (!data->unique)
	{
		if (!data->last)
			dup2(data->pipes[nb_pipe][1], STDOUT_FILENO);
		if (!data->first)
			dup2(data->pipes[nb_pipe - 1][0], STDIN_FILENO);
	}
	i = 0;
	while (i < data->pipe[data->code])
	{
		if (i != nb_pipe && i != nb_pipe - 1)
			ft_close(data, i);
		i++;
	}
	if (!data->first)
		ft_close(data, nb_pipe - 1);
	ft_close(data, nb_pipe);
	return (0);
}
