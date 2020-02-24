/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:54:46 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/11 16:02:05 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill(char *buf, char *str)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(buf, str)))
		return (NULL);
	free(buf);
	buf = NULL;
	return (tmp);
}
