/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:54:46 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/19 15:40:06 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_redir(char c, t_data *data, t_ms *lst, char *str)
{
	t_flux *new_flux;

	data->test = 1;
	if (!(new_flux = (t_flux *)malloc(sizeof(t_flux))))
		return (0);
	new_flux->redir = c;
	if (str[1] == '>' && str[0] == '>')
		new_flux->redir = 'a';
	new_flux->fichier = ft_strdup(lst->next->content);
	if (c == 'e')
		new_flux->fd = open(new_flux->fichier, O_RDWR);
	else
		new_flux->fd = open(new_flux->fichier, O_RDWR | O_CREAT, 0644);
	close(new_flux->fd);
	if (!test_directory(new_flux, new_flux->fichier))
		return (0);
	new_flux->next = NULL;
	ft_lstadd_back_flux(&data->flux, new_flux);
	return (1);
}

int		init_no_redir(t_data *data)
{
	t_flux *new_flux;

	if (data->test == 0)
	{
		if (!(new_flux = (t_flux *)malloc(sizeof(t_flux))))
			safe_exit(data);
		new_flux->redir = 'z';
		new_flux->fichier = NULL;
		new_flux->fd = 1;
		new_flux->next = NULL;
		ft_lstadd_back_flux(&data->flux, new_flux);
	}
	data->flux = data->begin_flux;
	return (1);
}

t_ms	*fill_databuf(t_data *data, t_ms *lst)
{
	if (!ft_strncmp(lst->content, "echo", 5) && lst->next != NULL &&
	!ft_strncmp(lst->next->content, "-n", 3))
		data->option_n ^= 1;
	lst = lst->next;
	if (data->option_n && lst)
		lst = lst->next;
	if (data->buf)
		free(data->buf);
	data->buf = ft_strdup(get_buffer(data, lst));
	data->test = 0;
	return (lst);
}

int		test_input(t_data *data, t_ms *lst, char *str)
{
	if (str[2] == '>' || str[2] == '<')
	{
		data->test = 1;
		free(data->buf);
		data->buf = ft_strdup("");
		ft_printf("syntax error near unexpected token '%c'\n", str[2]);
		return (0);
	}
	if (!lst->next)
	{
		data->test = 1;
		free(data->buf);
		data->buf = ft_strdup("");
		ft_printf("syntax error near unexpected token 'newline'\n");
		return (0);
	}
	return (1);
}

int		redir(t_data *data, t_ms *lst)
{
	data->begin_flux = data->flux;
	lst = fill_databuf(data, lst);
	while (lst)
	{
		data->str = ft_strdup(lst->content);
		if ((data->str[0] == '>' || data->str[0] == '<') && lst->sep == 0)
		{
			if (!test_input(data, lst, data->str))
				return (0);
			if (data->str[0] == '>' && !init_redir('w', data, lst, data->str))
				return (0);
			else if (data->str[0] == '<' && !init_redir('e', data, lst,
				data->str))
				return (0);
			if (!(lst = lst->next->next))
			{
				free(data->str);
				break ;
			}
		}
		else
			lst = lst->next;
		free(data->str);
	}
	return (init_no_redir(data));
}
