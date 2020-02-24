/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:17:56 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/18 19:44:34 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_set_pwd(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp("PWD", env->name, 4))
		{
			free(env->value);
			env->value = getcwd(0, 0);
			break ;
		}
		env = env->next;
	}
}

static	void	ft_cd_home(t_env *env)
{
	t_env	*env2;

	env2 = env;
	while (env)
	{
		if (!ft_strncmp(env->name, "HOME", 5))
		{
			chdir(env->value);
			ft_set_pwd(env2);
			return ;
		}
		env = env->next;
	}
	ft_printf("home not set\n");
	return ;
}

static int		ft_cd_error(char *path)
{
	ft_printf("%s: cd: %s: no such file or directory\n", PROMPT, path);
	return (1);
}

int				ft_cd(t_data *data, t_ms *lst)
{
	int		i;
	char	*path;
	t_env	*env;

	i = 0;
	env = data->lst_env;
	path = NULL;
	if (lst->next != NULL && lst->next->content != NULL)
		path = get_buffer(data, lst->next);
	if (lst->next == NULL || !ft_strncmp(path, "", 1))
	{
		ft_cd_home(env);
		return (0);
	}
	else
	{
		i = chdir(path);
		if (i != 0)
			return (ft_cd_error(path));
		ft_set_pwd(env);
	}
	data->buf = ft_strdup("");
	data->option_n = 1;
	write_redir(data);
	return (0);
}
