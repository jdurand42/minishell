/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:08:37 by jdurand           #+#    #+#             */
/*   Updated: 2020/02/17 12:40:56 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_comp_end(char *end, char *cdir_name)
{
	int		i;

	i = 0;
	if (ft_strlen(end) >= ft_strlen(cdir_name) - 1)
		return (1);
	return (ft_strncmp(end, &cdir_name[ft_strlen(cdir_name) - ft_strlen(end)],
	ft_strlen(end)));
}

char		*ft_ls(char *start, char *end)
{
	struct dirent		*cdir;
	char				*ls;
	DIR					*dir;

	ls = NULL;
	if (!(dir = opendir(".")))
		return (ft_strdup(""));
	while ((cdir = readdir(dir)))
	{
		if (cdir->d_name[0] == '.' ||
		ft_strncmp(start, cdir->d_name, ft_strlen(start))
		|| ft_comp_end(end, cdir->d_name))
			continue ;
		ls = ft_strjoin_1(ls, cdir->d_name);
		ls = ft_strjoin_1(ls, " ");
	}
	if (ls != NULL)
		ls[ft_strlen(ls) - 1] = 0;
	closedir(dir);
	return (ls);
}
