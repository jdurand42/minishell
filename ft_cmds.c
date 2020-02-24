/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:44:37 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/19 15:33:38 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_without_pipe(t_data *data, t_ms *lst, int i)
{
	if (data->pipe[data->code] > 0)
	{
		data->pipe[data->cmd_pipe] -= 1;
		data->code += 1;
		exec_a_cmd(data, lst);
		free_pipe_cmd(data);
	}
	else
	{
		if (i == 1 && ft_cd(data, lst) == 1)
			ft_ret_erreur(data, 1);
		else if (i == 2)
			ft_exit(data, lst);
		else if (i == 3)
			ft_unset(&data, lst);
		else if (i == 4)
			ft_export(data, lst);
	}
	return ;
}

void	test_pipe_export(t_data *data, t_ms *lst)
{
	if (!data->pipe[data->code])
		cmd_without_pipe(data, lst, 4);
	else
		data->no_arg = 0;
}

void	exec_cmd(t_data *data, t_ms *lst)
{
	data->no_arg = 1;
	if (lst == NULL)
		return ;
	if (is_add_var(&lst))
	{
		add_var(data, lst);
		return ;
	}
	else if (ft_strncmp(lst->content, "cd", 3) == 0 && !data->pipe[data->code])
		cmd_without_pipe(data, lst, 1);
	else if (ft_strncmp(lst->content, "exit", 5) == 0 &&
		!data->pipe[data->code])
		cmd_without_pipe(data, lst, 2);
	else if (ft_strncmp(lst->content, "unset", 6) == 0 &&
		!data->pipe[data->code])
		cmd_without_pipe(data, lst, 3);
	else if (ft_strncmp(lst->content, "export", 7) == 0 && (lst->next != NULL
	&& ft_strncmp(ft_write_args(data, get_buffer(data, lst->next), 0), "", 1)))
		test_pipe_export(data, lst);
	else
	{
		exec_a_cmd(data, lst);
		free_pipe_cmd(data);
	}
}

int		str_is_digit(t_ms *lst)
{
	int		i;
	char	*str;

	i = 0;
	if (lst->next)
	{
		str = ft_strdup(lst->next->content);
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
			{
				free(str);
				return (0);
			}
			i++;
		}
		free(str);
	}
	else
		return (0);
	return (1);
}

void	ft_echo(t_data *data)
{
	delete_space(data->buf);
	write_redir(data);
	exit(0);
}
