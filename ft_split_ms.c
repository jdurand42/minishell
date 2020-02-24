/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:09:18 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/18 15:30:22 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_cmp_set(char c, char *set, int *flag, int *as)
{
	int	i;

	i = 0;
	if (*as == 1)
	{
		*as = 0;
		return (0);
	}
	if (c == 92 && *flag != 2)
	{
		*as = 1;
		return (0);
	}
	if (c == 34 && *flag != 2)
		*flag ^= 1;
	if (c == 39 && *flag != 1)
		*flag ^= 2;
	while (set[i] != 0 && *flag == 0)
	{
		if (set[i] == c && *flag == 0)
			return (1);
		i++;
	}
	return (0);
}

static char		*ft_strndup_bonus(char const *src, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!(dest = (char*)malloc((n + 1) * sizeof(char))))
		return (NULL);
	else
	{
		while (src[i] != '\0' && i < n)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
}

static char		**free_split(char **tab, int j)
{
	while (j >= 0)
	{
		free(tab[j--]);
	}
	free(tab);
	return (NULL);
}

static void		init_vars(t_split_var *var)
{
	var->i = 0;
	var->j = 0;
	var->st = 0;
	var->flag = 0;
	var->as = 0;
}

char			**ft_split_ms(char const *s, char *set, int size)
{
	t_split_var	var;
	char		**tab;

	init_vars(&var);
	if (!(tab = (char**)malloc((size + 1) * sizeof(char*))))
		return (NULL);
	while (var.j < size)
	{
		while (s[var.i] != 0 && ft_cmp_set(s[var.i], set, &var.flag,
		&var.as))
			var.i += 1;
		var.st = var.i;
		if (var.i == 0 && var.flag != 0)
			var.i += 1;
		while (s[var.i] != 0 && !ft_cmp_set(s[var.i], set, &var.flag,
		&var.as))
			var.i += 1;
		if (!(tab[(var.j)++] = ft_strndup_bonus(&s[var.st],
		var.i - var.st)))
			return (free_split(tab, var.j));
		if (s[var.i] != 0)
			var.i += 1;
	}
	tab[var.j] = 0;
	return (tab);
}
