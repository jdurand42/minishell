/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:19:47 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/14 16:35:30 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_abs(int x)
{
	return (x < 0 ? -x : x);
}

static void		ft_sort(char **tab)
{
	int		i;
	int		j;
	int		n;
	char	*b;

	i = 0;
	j = 0;
	while (tab[i] != 0)
	{
		j = i + 1;
		while (tab[j] != 0)
		{
			n = ft_abs(ft_strchr(tab[i], '=') - ft_strchr(tab[j], '='));
			if (ft_strncmp(tab[i], tab[j], n) > 0)
			{
				b = tab[i];
				tab[i] = tab[j];
				tab[j] = b;
			}
			else
				j++;
		}
		i++;
	}
	tab[i - 1][ft_strlen(tab[i - 1]) - 1] = 0;
}

static void		ft_fill_tab(char **tab, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->exp)
		{
			tab[i] = ft_strjoin("declare -x ", env->name);
			tab[i] = ft_strjoin_1(tab[i], "=\"");
			tab[i] = ft_strjoin_2(tab[i], ft_strjoin(env->value, "\"\n"));
			i++;
		}
		env = env->next;
	}
	tab[i] = 0;
}

void			ft_export_no_arg(t_data *data)
{
	char	**tab;
	int		i;
	int		size;

	size = ft_envsize(data->lst_env);
	i = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * (size + 1))))
		return ;
	ft_fill_tab(tab, data->lst_env);
	ft_sort(tab);
	while (tab[i] != 0)
		data->buf = ft_strjoin_1(data->buf, tab[i++]);
	i = 0;
	write_redir(data);
	while (size)
		free(tab[size--]);
	free(tab);
	exit(0);
}
