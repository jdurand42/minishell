/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit_ms2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:34:58 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/17 16:37:24 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_do_empty_quotes2(char **b, int *i, int *flag, t_split_var2 *var)
{
	if (var->cmp == 1 && var->s[*i] == 34 && (*flag & 4) && !(*flag & 2) &&
	!check_if_last(var->s, *i + 2) && var->s[*i + 1] == 34)
	{
		if (var->s[*i + 2] != 0 && var->s[*i + 2] == 32)
		{
			*b = ft_strjoin_1(*b, "\" \"");
			*flag = 1;
			*i += 3;
		}
	}
	else if (var->cmp == 1 && var->s[*i] == 39 && (*flag & 2) && !(*flag & 4) &&
	!check_if_last(var->s, *i + 2) && var->s[*i + 1] == 39)
	{
		if (var->s[*i + 2] != 0 && var->s[*i + 2] == 32)
		{
			*b = ft_strjoin_1(*b, "\' \'");
			*flag = 1;
			*i += 3;
		}
	}
	else
		*b = ft_strjoin_2(*b, ft_strndup(&var->s[(*i)++], 1));
}

char		*ft_do_empty_quotes(char *s)
{
	int				i;
	int				flag;
	t_ms			nada;
	char			*b;
	t_split_var2	var;

	i = 0;
	flag = 1;
	b = ft_strdup("");
	var.s = s;
	while (s[i] != 0)
	{
		var.cmp = ft_cmp_set_ms(s[i], &flag, &nada, check_if_zero(i));
		ft_do_empty_quotes2(&b, &i, &flag, &var);
	}
	return (b);
}

int			check_if_last(char *s, int i)
{
	while (s[i] != 0)
	{
		if (s[i] != 32)
			return (0);
		i++;
	}
	return (1);
}
