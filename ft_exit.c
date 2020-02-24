/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:21:00 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/18 18:49:26 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, t_ms *lst)
{
	int		flag;
	char	*str;

	flag = str_is_digit(lst);
	str = NULL;
	if (lst->next && lst->next->next && lst->next->next->content)
		str = ft_strdup(lst->next->next->content);
	if (lst->next == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
	else if (flag == 1 && str != NULL)
	{
		ft_printf("exit\nexit: too many arguments\n");
		ft_ret_erreur(data, 1);
		free(str);
	}
	else
	{
		ft_printf("exit\n");
		if (flag == 0)
			ft_printf("exit : numeric argument required\n");
		exit(ft_atoi(lst->next->content));
	}
}
