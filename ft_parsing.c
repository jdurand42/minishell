/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:37:25 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/19 16:22:25 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strjoinch(char const *s1, char c)
{
	char	*new_str;
	size_t	i;
	size_t	s1_len;

	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	new_str = ft_strnew(s1_len + 2);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	*(new_str + i) = c;
	return (new_str);
}

static int	ft_check_nl(char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void		handler(int i)
{
	ft_printf("\n%s$:", PROMPT);
	i = 0;
}

void		parse_stdin(t_data *data)
{
	int		ret;
	char	*b_line;
	char	buffer[1024];

	data->entry = NULL;
	while ((ret = read(STDIN_FILENO, buffer, 1)) >= 0)
	{
		buffer[ret] = 0;
		if (ret == 0 && data->entry == NULL)
			return ;
		if (buffer[0] == EOF)
			continue ;
		signal(SIGINT, handler);
		b_line = data->entry;
		data->entry = ft_strjoinch(b_line, buffer[0]);
		free(b_line);
		b_line = NULL;
		if (ft_check_nl(data->entry))
			break ;
	}
	if (ret < 0)
		perror("Lecture: \n");
}

void		parse_a_cmd(t_data *data)
{
	int		j;
	char	*s;
	t_ms	*b;

	j = 0;
	parse_sep(data);
	data->n_cmds = ft_strlen(data->sep) + 1;
	j = 0;
	data->cmds = ft_split_ms(data->entry, "|;&\n", data->n_cmds);
	data->lst = malloc((data->n_cmds + 1) * sizeof(t_list*));
	while (data->cmds[j] != 0)
	{
		data->lst[j] = ft_lstsplit_ms(data->cmds[j]);
		if (data->lst[j] != 0)
		{
			s = ft_strjoin("|arg|-| ", data->lst[j]->content);
			b = ft_lstsplit_ms(s);
			free(data->lst[j]->content);
			free(s);
			data->lst[j]->content = ft_strdup(get_buffer(data, b->next));
			ft_lstclear_ms(&b, free);
		}
		j++;
	}
	data->lst[j] = 0;
}
