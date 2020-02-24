/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:53:46 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/19 12:09:06 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_write_antislash(char **toprint, int *i, int sep, char *b)
{
	if (b[*i] == 92)
	{
		if (sep == 0 || (b[*i + 1] == '$' && sep != 2) ||
		(sep == 1 && b[*i + 1] == 34))
		{
			*toprint = ft_strjoin_2(*toprint, ft_strndup(&b[++(*i)], 1));
			*i += 1;
		}
		else
		{
			*toprint = ft_strjoin_1(*toprint, "\\");
			i += 1;
		}
	}
}

static void		ft_write_args2(t_data *data, char **toprint, char *b, int sep)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (b[i] != 0 && sep != 2)
	{
		if (b[i] != '$')
		{
			k = i;
			while (b[k] != 0 && b[k] != '$' && b[k] != 92)
				k++;
			*toprint = ft_strjoin_2(*toprint, ft_strndup(&b[i], k - i));
			i = k;
		}
		else if (b[i] == '$' && sep != 2)
		{
			*toprint = ft_strjoin_2(*toprint, get_var(data, &b[++i], &i));
			while (ft_isalnum(b[i]))
				i++;
		}
		ft_write_antislash(toprint, &i, sep, b);
	}
}

char			*ft_write_args(t_data *data, char *b, int sep)
{
	int		i;
	int		k;
	char	*toprint;

	i = 0;
	k = 0;
	toprint = ft_strdup("");
	if (sep == 2)
	{
		toprint = ft_strjoin_1(toprint, b);
		return (add_garbage_ret(data, (void**)&toprint));
	}
	else
		ft_write_args2(data, &toprint, b, sep);
	return (add_garbage_ret(data, (void**)&toprint));
}

char			*get_var(t_data *data, char *b, int *inc)
{
	int		i;
	char	*name;

	i = 0;
	if (!ft_strncmp(b, "?", 1))
	{
		*inc += 1;
		return (ft_strdup(get_var_env(data->lst_env, "?")));
	}
	if (!ft_isalnum(b[i]))
	{
		return (ft_strdup("$"));
	}
	while (b[i] != 0 && ft_isalnum(b[i]))
		i++;
	name = ft_strndup(b, i);
	*inc += i;
	if (name == NULL || ft_strlen(name) == 0)
	{
		free(name);
		return (ft_strdup(""));
	}
	free(name);
	return (ft_strdup(get_var_env(data->lst_env, name)));
}

char			*get_var_env(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(env->name) + 1))
			return (env->value);
		env = env->next;
	}
	return ("");
}
