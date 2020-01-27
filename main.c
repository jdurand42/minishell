/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:58:29 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/27 13:42:00 by jdurand          ###   ########.fr       */
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

int main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*cmd;
	int 	code;

	data.gb_collector = NULL;

	init_data(&data, envp);
	while (1)
	{
		code = 0;
		ft_printf("%s", PROMPT);
		parse_stdin(&data);
		parse_a_cmd(&data);
		printf("%d\n", data.n_cmds);
		while (data.entry && code <= data.n_cmds && data.lst != NULL)
		{
			exec_cmd(&data, data.lst[code]);
			code += 1;
		}
		ft_free_lst(&data, data.lst);
		init_data(&data, envp);

	}
	//safe_exit(&data);
	return (0);
}
