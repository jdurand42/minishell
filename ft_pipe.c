/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:06:55 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/19 15:43:15 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_exec_cmd(t_data *data, int nb_pipe, t_ms *lst, char **env)
{
	int i;

	test_builtin(data);
	if (ft_strncmp(data->cmds_pipe[nb_pipe], "pwd", 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp(data->cmds_pipe[nb_pipe], "env", 4) == 0)
		ft_env(data, lst);
	else if (ft_strncmp(data->cmds_pipe[nb_pipe], "export", 7) == 0)
		ft_export_no_arg(data);
	else
	{
		i = 0;
		if (execve(lst->content, data->split_pipe[nb_pipe], env) != -1)
			return (1);
		while (execve(data->tab_path[nb_pipe][i], data->split_pipe[nb_pipe],
			env) == -1 && data->tab_path[nb_pipe][i] != NULL)
			i++;
		test_path(data, i);
		test_path_null(data, i);
	}
	return (4);
}

void		ft_redir_pipe(t_data *data)
{
	if ((data->flux->redir == 'a' || data->flux->redir == 'w'))
	{
		if (data->flux->redir == 'a')
			data->redir_out = open(data->flux->fichier, O_RDWR
			| O_CREAT | O_APPEND);
		if (data->flux->redir == 'w')
			data->redir_out = open(data->flux->fichier, O_RDWR
			| O_CREAT | O_TRUNC);
		if (data->redir_out < 0)
			msg_erreur(data);
		dup2(data->redir_out, STDOUT_FILENO);
		close(data->redir_out);
	}
	else if (data->flux->redir == 'e')
	{
		data->redir_in = open(data->flux->fichier, O_RDWR);
		if (data->redir_in < 0)
			msg_erreur(data);
		dup2(data->redir_in, STDIN_FILENO);
		close(data->redir_in);
	}
}

t_flux		*get_flux(t_data *data, int nb_pipe)
{
	int i;

	i = 0;
	while (i <= nb_pipe)
	{
		if (data->flux->next)
			data->flux = data->flux->next;
		i++;
	}
	data->last = (nb_pipe == data->pipe[data->cmd_pipe]);
	return (data->flux);
}

int			ft_pipe(t_data *data, char **env, t_ms *lst)
{
	init_data_pipe(data);
	while (data->nb_pipe <= data->pipe[data->cmd_pipe])
	{
		if (!redir(data, data->lst[data->code + data->nb_pipe]))
			return (0);
		data->begin_flux = data->flux;
		data->flux = get_flux(data, data->nb_pipe);
		if ((data->pid = fork()) < 0)
		{
			perror("fork");
			return (4);
		}
		if (data->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup_pipe(data, data->nb_pipe);
			ft_redir_pipe(data);
			return (ft_exec_cmd(data, data->nb_pipe, lst, env));
		}
		else
			process_pere(data, data->nb_pipe, data->begin_flux);
	}
	return (0);
}

int			process_pere(t_data *data, int nb_pipe, t_flux *begin)
{
	int ret;
	int status;

	data->child = 1;
	while (data->child)
	{
		if (!data->first)
			close(data->pipes[nb_pipe - 1][1]);
		ret = wait(&status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				ft_ret_erreur(data, 130);
			else if (WTERMSIG(status) == 3)
				ft_ret_erreur(data, 131);
		}
		else
			ft_ret_erreur(data, WEXITSTATUS(status));
		if (ret == data->pid)
			data->child = 0;
	}
	data->first = 0;
	data->nb_pipe += 1;
	data->flux = begin;
	return (0);
}
