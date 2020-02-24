/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:15:29 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/19 16:25:10 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_flag(t_data *data, int flag, int i)
{
	if (data->entry[i] == 34 && flag != 2)
		flag = (flag == 0 ? 1 : 0);
	if (data->entry[i] == 39 && flag != 1)
		flag = (flag == 0 ? 2 : 0);
	return (flag);
}

static void	parse_sep_2(t_data *data, int i, int *j, int *k)
{
	if (i > 0 && data->entry[i - 1] != 92)
	{
		data->sep = ft_strjoin_2(data->sep, ft_strndup(&data->entry[i], 1));
		*j += 1;
		if (data->entry[i] == '|' && (*j > 0 && (!data->sep[*j] ||
		data->sep[*j - 1] == '|')))
		{
			if (data->entry[i + 1] && data->entry[i + 1] == '|')
			{
				ft_printf("Parse error near '|'\n");
				free(data->entry);
				data->entry = ft_strdup("\0");
			}
			data->pipe[*k] += 1;
		}
		else
		{
			*k += 1;
			data->pipe[*k] = 0;
		}
	}
}

void		parse_sep(t_data *data)
{
	int i;
	int j;
	int k;
	int flag;

	i = 0;
	j = 0;
	k = 0;
	flag = 0;
	data->sep = ft_strdup("");
	while (data->entry[i] != 0)
	{
		if (data->entry[check_if_zero(i)] != 92)
			flag = get_flag(data, flag, i);
		if (data->entry[check_if_zero(i)] == 92 && flag == 2)
			flag = get_flag(data, flag, i);
		if (flag == 0 && is_sep(data->entry[i]))
			parse_sep_2(data, i, &j, &k);
		i++;
	}
	data->sep[j] = 0;
}
