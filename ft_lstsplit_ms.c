/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit_ms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:20:11 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/27 13:24:40 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "./libft/libft.h"

static int    ft_cmp_set(char c, int  *flag)
{
	unsigned char   pc;
	int				i;

	if (c == 34 && *flag != 2)
	{
		(*flag == 0) ? (*flag = 1) : (*flag = 0);
		return (1);
	}
	if (c == 32)
	{
		if (*flag == 0)
			return (1);
	}
	if (c == 39 && *flag != 1)
	{
		(*flag == 0) ? (*flag = 2) : (*flag = 0);
		return (1);
	}
	return (0);
}

static int    count_words(char const *s, char *set)
{
    unsigned int    i;
    unsigned int    size;
    int             flag;
    i = 0;
    size = 0;
    flag = 0;
    while (s[i] != 0)
    {
        if (i > 0 && (ft_cmp_set(s[i], &flag)) && !(ft_cmp_set(s[i - 1], &flag)))
            size++;
        i++;
    }
    if (i > 0 && !(ft_cmp_set(s[i - 1], &flag)))
        size++;
    return (size);
}

t_list        *ft_lstsplit_ms(char const *s, char *set)
{
    unsigned int    i;
    unsigned int    st;
    t_list            *list;
    unsigned int    size;
	int           flag;
    i = 0;
    list = NULL;
    st = 0;
    size = count_words(s, set);
	flag = 0;

	while (size--)
	{
    	while (s[i] != 0 && ft_cmp_set(s[i], &flag))
            i++;
        st = i;
        while (s[i] != 0 && !ft_cmp_set(s[i], &flag))
            i++;
        ft_lstadd_back(&list, ft_lstnew(ft_strndup(&s[st], i - st)));
		i++;
    }
    return (list);
}
