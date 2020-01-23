/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:58:29 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/23 17:59:28 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_test_gb(t_data *data)
{
	char *b = safe_malloc(12 + 1, sizeof(char), data);
	b[0] = 'a';
//	printf("%s\n", b);
	char *c = safe_malloc(13 + 1, sizeof(char), data);
	int *d = safe_malloc(15 + 1, sizeof(int), data);
	int **tab;

	tab = safe_malloc(8, sizeof(int*), data);
	for (int i = 0; i < 8; i++)
		tab[i] = safe_malloc(10, sizeof(int), data);
}

int main()
{
	t_data	data;
	char	*cmd;

	data.gb_collector = NULL;
	init_data(&data);
	while (1)
	{
		ft_printf("%s :", PROMPT);
		parse_stdin(&data); // re_rum if "" not closed
	//	ft_printf("%s\n", data.entry);
		if (data.entry != 0 && ft_strncmp(data.entry, "exit\n", 5) == 0)
			safe_exit(&data);
		//if (!data.entry)
		//	continue ;
		parse_a_cmd(&data);
		//print_cmds(&data);
		init_data(&data);

	}
	//safe_exit(&data);
	return (0);
}
