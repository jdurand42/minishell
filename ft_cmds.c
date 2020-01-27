/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:44:37 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/27 12:50:47 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	exec_cmd(t_data *data, t_list *lst)
{
	if (!(lst != NULL))
		return ;
	//ft_get_env(data, &lst);
	if (ft_strncmp(lst->content, "echo", 4) == 0)
		ft_echo(data, lst);
	else if (ft_strncmp(lst->content, "pwd", 3) == 0)
		ft_pwd(data, lst);
	else if (ft_strncmp(lst->content, "cd", 2) == 0)
		ft_cd(data, lst);
	else if (ft_strncmp(lst->content, "env", 3) ==  0)
		ft_env(data, lst);
	else if (ft_strncmp(lst->content, "exit", 4) == 0)
		ft_exit(data, lst);
}

void 	ft_env(t_data *data, t_list *lst)
{
	int i;

	i = 0;
	if (lst->next != NULL)
		ft_printf("env: too many arguments\n");
	else
	{
		while(data->envp[i] != NULL)
		{
			ft_printf("%s\n", data->envp[i]);
			i++;
		}
	}
}

void 	ft_exit(t_data *data, t_list *lst)
{
	ft_printf("[process completed]\n");
	safe_exit(data);
}

void 	ft_echo(t_data *data, t_list *lst)
{
	int		j;
	int 	option;

	j = 0;
	option = 0;
	lst = lst->next;
	if (ft_strncmp(lst->content, "-n", 2) == 0)
	{
		option ^= 1;
		lst = lst->next;
	}
	while (lst != 0)
	{
		ft_printf("%s", lst->content);
		if (lst->next != NULL)
			ft_printf("/");
		lst = lst->next;
	}
	if (option)
		ft_printf("%%");
	ft_printf("\n");
}

void 	ft_cd(t_data *data, t_list *lst)
{
	int i;

	i = 0;
	if (lst->next == 0)
	{
		printf("changng dir to roots\nnot implemented yet\n");
		while (data->envp[i] != NULL)
		{
			if (ft_strncmp(data->envp[i], "HOME=", 5) == 0)
			{
				chdir(&data->envp[i][5]);
				break ;
			}
			i++;
		}
	}
	else
	{
		lst = lst->next;
		i = chdir(lst->content);
		if (i != 0)
			ft_printf("cd: no such file or directory: %s\n", lst->content);
	}
}

void 	ft_pwd(t_data *data, t_list *lst)
{
	char *b;

	b = NULL;
	if (lst->next != NULL)
	{
		ft_printf("pwd: too many arguments");
		return ;
	}
	if (!(b = getcwd(b, 0)))
	{
		ft_printf("Malloc error\n");
		safe_exit(data);
	}
	ft_printf("%s\n", b);
	free(b);
}
