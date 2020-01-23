/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:37:25 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/23 17:18:43 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	ft_check_nl(char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void 	parse_stdin(t_data *data)
{
	int		ret;
	char	*file;
	char	*b_line;
	char	buffer[1024];

 	data->entry = NULL;
	while ((ret = read(0, buffer, 1024)) > 0)
	{
		printf("%d\n", ret);
		buffer[ret] = 0;
		b_line = data->entry;
		data->entry = ft_strjoin(data->entry, buffer);
		free(b_line);
		b_line = NULL;
		if (ft_check_nl(data->entry))
			break ;
	}
	if (file)
		ft_lstadd_front(&data->gb_collector, ft_lstnew(file));
//	printf("%s\n", data->entry);
}
/*
** split?
**
**
*/

void 	parse_sep(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	data->sep = safe_malloc(data->n_cmds + 1, sizeof(char), data);
	while (data->entry[i] != 0)
	{
		if (is_sep(data->entry[i]))
			data->sep[j] = data->entry[j];
		j++;
	}
}

void 	parse_a_cmd(t_data *data)
{
	int j;
	int id_cmds;
	int id_args;

	j = 0;
	id_cmds = 0;
	while (data->entry[j] != 0)
	{ // count cmds
		if (is_sep(data->entry[j]))
			data->n_cmds += 1;
		j++;
	}
	parse_sep(data);
	j = 0;
	data->cmds = ft_split_set(data->entry, "|;&\n");
	ft_lstadd_front(&data->gb_collector, ft_lstnew(data->cmds));
	while (data->cmds[j] != 0)
	{
		ft_lstadd_front(&data->gb_collector, ft_lstnew(data->cmds[j]));
		j++;
	}
	for (int i = 0; data->cmds[i] != 0; i++)
		printf("%d: %s\n", 	i, data->cmds[i]);
}
