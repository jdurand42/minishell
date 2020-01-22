/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:58:29 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/22 19:49:41 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	t_data data;

	data.gb_collector = NULL;

	char *b = safe_malloc(12 + 1, sizeof(char), &data);
	b[0] = 'a';
//	printf("%s\n", b);
	char *c = safe_malloc(13 + 1, sizeof(char), &data);
	int *d = safe_malloc(15 + 1, sizeof(int), &data);
//	printf("%d\n", d[0]);
	safe_exit(&data);
	return (0);
}
