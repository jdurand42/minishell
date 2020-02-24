/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:41:18 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/17 12:41:27 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_add_var(t_ms **alst)
{
	int		i;
	t_ms	*buffer;
	char	*s;

	buffer = *alst;
	while (buffer)
	{
		i = 0;
		s = (char*)buffer->content;
		while (s[i] != 0 && s[i] != '=')
		{
			if (!ft_isalpha(s[i]) && i == 0)
				return (0);
			if (!ft_isalnum(s[i]))
				return (0);
			i++;
		}
		if (s[i] != '=')
		{
			*alst = buffer;
			return (0);
		}
		buffer = buffer->next;
	}
	return (1);
}

void		add_var(t_data *data, t_ms *lst)
{
	int		i;
	t_env	*env;
	char	*s;

	while (lst)
	{
		if (!(env = (t_env*)malloc(sizeof(t_env))))
			return ;
		i = 0;
		s = (char*)lst->content;
		while (s[i] != 0 && s[i] != '=')
			i++;
		env->name = ft_strndup(s, i);
		env->value = ft_parse_var_value(&s[i + 1]);
		env->exp = 0;
		ft_lstadd_back_env(&data->lst_env, env);
		lst = lst->next;
	}
}

static void	fonction_nul(int *i, int *j, int *flag)
{
	*i = 0;
	*j = 0;
	*flag = 0;
}

char		*ft_parse_var_value(char *value)
{
	int		i;
	int		j;
	int		flag;
	char	*b;

	fonction_nul(&i, &j, &flag);
	if (!(b = (char*)malloc((ft_strlen(value) + 1) * sizeof(char))))
		return (NULL);
	while (value[i] != 0)
	{
		if (value[i] != 34 && value[i] != 39)
			b[j++] = value[i];
		if (value[i] == 34 && flag == 2)
			b[j++] = value[i];
		else if (value[i] == 34 && flag == 0)
			flag = (flag == 0 ? 1 : 0);
		if (value[i] == 39 && flag == 1)
			b[j++] = value[i];
		else if (value[i] == 39 && flag == 0)
			flag = (flag == 0 ? 2 : 0);
		i++;
	}
	b[i] = 0;
	return (b);
}
