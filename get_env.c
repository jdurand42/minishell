/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:30:56 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/11 17:24:35 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_env(char **cmds, t_env **var_env)
{
	int		i;
	t_env	*liste;
	char	*str;

	i = 0;
	while (cmds[i] != NULL)
	{
		liste = *var_env;
		str = cmds[i];
		if (str[0] == '$')
		{
			while (liste != NULL)
			{
				if (ft_strncmp(liste->name, str + 1, ft_strlen(str)) == 0)
				{
					free(cmds[i]);
					cmds[i] = ft_strdup(liste->value);
				}
				liste = liste->next;
			}
		}
		i++;
	}
	return (1);
}

int		ft_copyuntil(char **dst, char *src, char c)
{
	int		j;
	int		i;
	char	*buf;

	j = -1;
	while (src[++j])
		if (src[j] == c)
			break ;
	if (!(buf = ft_strnew(j)))
		return (0);
	i = 0;
	while (i < j && src[i])
	{
		buf[i] = src[i];
		i++;
	}
	buf[i] = '\0';
	*dst = buf;
	return (j);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env *tmp;

	if (*alst && new)
	{
		tmp = *alst;
		if (!(*alst))
		{
			*alst = new;
			return ;
		}
		while (tmp != NULL && tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	else if (alst)
		*alst = new;
	return ;
}

t_env	*init_maillon(char *name, char *value, int exp)
{
	t_env *new_env;

	if (!(new_env = malloc(sizeof(t_env))))
		return (0);
	new_env->name = name;
	new_env->value = value;
	new_env->exp = exp;
	new_env->next = NULL;
	return (new_env);
}

t_env	*init_env(char **envp)
{
	int		j;
	char	*str;
	char	*name;
	char	*value;
	t_env	*liste;

	name = NULL;
	value = NULL;
	liste = NULL;
	while (*envp != NULL)
	{
		str = *envp;
		j = ft_copyuntil(&name, str, '=');
		ft_copyuntil(&value, &str[j + 1], '\0');
		ft_lstadd_back_env(&liste, init_maillon(name, value, 1));
		envp++;
	}
	ft_lstadd_back_env(&liste, init_maillon("?", ft_strdup("0"), 0));
	return (liste);
}
