/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:37:25 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/24 12:15:40 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int 	ft_check_nl(char *s)
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
	while ((ret = read(0, buffer, 1023)) > 0)
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
	if (data->entry)
		ft_lstadd_front(&data->gb_collector, ft_lstnew(data->entry));
}
/*
** split?
**
**
*/

void 	skip_spaces(char *s, int *i)
{
	if (s != NULL)
	{
		printf("%s\n", &s[*i]);
		while (s[*i] != 0 && s[*i] == 32)
		{
			printf("skip pete\n");
			*i += 1;
		}
	}
}


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
		{
			data->sep[j] = data->entry[i];
			j++;
		}
		i++;
	}
	data->sep[j] = 0;
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
	printf("%d\n", data->n_cmds);
	data->cmds = ft_split_set(data->entry, "|;&\n");
	data->lst = safe_malloc(data->n_cmds + 1, sizeof(t_list*), data);
	ft_lstadd_front(&data->gb_collector, ft_lstnew(data->cmds));
	while (data->cmds[j] != 0)
	{
		data->lst[j] = ft_splitlst(data->cmds[j], " ");
		ft_lstadd_front(&data->gb_collector, ft_lstnew(data->cmds[j]));
		j++;
	}
	for (int i = 0; data->cmds[i] != 0; i++)
		printf("%d: %s\n", 	i, data->cmds[i]);
	printf("seps: %s\n----\n", data->sep);
}
