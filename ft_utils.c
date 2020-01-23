/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:41:22 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/23 17:42:09 by jdurand          ###   ########.fr       */
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

char 	*ft_strdup_skip(t_data *data, char *s)
{
	int j;
	int k;
	char *b;

	j = 0;
	k = 0;
	while (s[data->i] != 0 && s[data->i] == 32)
		data->i += 1;
	j = data->i;
	while (s[j] != 0 && ft_isalpha(s[j]))
		j++;
	b = safe_malloc(j - data->i + 1, sizeof(char), data);
	while (s[data->i] != 0 && data->i < j)
	{
		b[k++] = s[data->i];
		data->i += 1;
	}
	if (s[data->i] != 0 && !is_sep(s[data->i]))
		data->i += 1;
	b[k] = 0;
	return (b);
}
