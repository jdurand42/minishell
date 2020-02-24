/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_directiry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:15:41 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/14 16:15:51 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		test_directory(t_flux *flux, char *str)
{
	struct stat	buf;
	int			ret;

	ret = stat(flux->fichier, &buf);
	if (ret < 0)
		ft_printf("%s:%s\n:", flux->fichier, strerror(errno));
	if (S_ISDIR(buf.st_mode))
	{
		ft_printf("%s: is a directory\n", str);
		return (0);
	}
	return (1);
}
