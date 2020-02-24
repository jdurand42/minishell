/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:22:36 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/11 17:33:52 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size + 1)
		*(str + i++) = 0;
	return (str);
}

void	ft_lstadd_back_flux(t_flux **alst, t_flux *new)
{
	t_flux *tmp;

	if (alst && new)
	{
		tmp = *alst;
		if (!(*alst))
		{
			*alst = new;
			return ;
		}
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return ;
}
