/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:58:02 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/18 19:23:50 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**parse_path_null(void)
{
	char	**path;

	if (!(path = (char**)malloc(2 * sizeof(char*))))
		return (NULL);
	path[0] = ft_strdup("");
	path[1] = 0;
	return (path);
}

char		**parse_path(t_env *env)
{
	char	**path;
	int		i;

	i = 0;
	while (env)
	{
		if (!ft_strncmp(env->name, "PATH", 5))
		{
			path = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		path = parse_path_null();
	else
	{
		while (path[i] != 0)
		{
			path[i] = ft_strjoin_1(path[i], "/");
			i++;
		}
	}
	return (path);
}

char		**parse_env(t_env *env)
{
	int		i;
	int		size;
	char	**envt;
	char	*tmp;

	i = 0;
	size = ft_envsize(env);
	if (!(envt = (char**)malloc((size + 1) * sizeof(char *))))
		return (NULL);
	while (i < size)
	{
		if (env->exp == 1)
		{
			tmp = ft_strjoin(env->name, "=");
			if (!(envt[i] = ft_strjoin(tmp, env->value)))
				return (NULL);
			if (tmp)
				free(tmp);
			i++;
		}
		env = env->next;
	}
	envt[i] = 0;
	return (envt);
}

int			exec_a_cmd(t_data *data, t_ms *lst)
{
	char	**envt;
	int		i;
	int		ret;
	int		size;

	size = ft_envsize(data->lst_env);
	envt = parse_env(data->lst_env);
	ret = ft_pipe(data, envt, lst);
	if (ret != 0)
		ft_printf("erreur : %d\n", ret);
	i = 0;
	while (i < size)
	{
		free(envt[i]);
		envt[i] = NULL;
		i++;
	}
	free(envt[i]);
	free(envt);
	return (1);
}
