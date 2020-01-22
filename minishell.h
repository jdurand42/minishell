/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:59:42 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/22 19:49:54 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
//#include <fctnl.h>
#include <unistd.h>
#include "libft/libft.h"

typedef struct	s_data
{
	struct s_list *gb_collector;
}				t_data;

void	*safe_malloc(size_t n, size_t n_size, t_data *data);
void 	safe_exit(t_data *data);
