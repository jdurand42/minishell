/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:05:30 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/18 18:21:13 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_empty(char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int		ft_error_sep(t_data *data)
{
	ft_printf("Parse error near 'end of file'\n");
	ft_ret_erreur(data, 258);
	return (0);
}

int		ft_check_pipes(t_data *data)
{
	int i;

	i = 0;
	while (data->sep[i] != 0)
	{
		if (data->sep[i] == '|' && data->cmds[i + 1] == 0)
			return (ft_error_sep(data));
		else if (data->sep[i] == '|' && ft_is_empty(data->cmds[i + 1]))
			return (ft_error_sep(data));
		else if (data->sep[i] == ';' && data->sep[i + 1] == ';')
		{
			if (data->cmds[i + 1] == 0)
				return (ft_error_sep(data));
			else if (ft_is_empty(data->cmds[i + 1]))
				return (ft_error_sep(data));
		}
		i++;
	}
	return (1);
}

void	ft_free_all(t_data *data)
{
	ft_free_lst(data->lst);
	free_cmds(data->cmds);
	ft_lstclear(&data->gb_collector2, free);
}

int		main(int argc, char **av, char **envp)
{
	t_data	data;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	init_data_start(&data, envp, argc, av);
	while (1)
	{
		ft_printf("%s$: ", PROMPT);
		parse_stdin(&data);
		if (data.entry == NULL)
			return (ft_printf("exiting...\n"));
		parse_a_cmd(&data);
		while (data.entry && data.lst[data.code] != NULL && data.lst != NULL)
		{
			if (!ft_check_pipes(&data))
				break ;
			exec_cmd(&data, data.lst[data.code]);
			init_cmd(&data);
			data.code += data.pipe[data.cmd_pipe] + 1;
			data.cmd_pipe++;
		}
		ft_free_all(&data);
		init_data(&data);
	}
	return (0);
}
