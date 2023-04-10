/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:35 by naterrie          #+#    #+#             */
/*   Updated: 2023/04/10 16:29:18 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <stdio.h>

void	setpath(t_pipex	*pipex, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strlen(env[i]) >= 5 && ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pipex->path = ft_substr(env[i], 5, ft_strlen(env[i]));
			return ;
		}
		i++;
	}
	if (!env[i])
		exit(1);
}

int	ft_checkfile(char **argv, int argc, t_pipex *pipex)
{
	pipex->fdin = open(argv[1], O_RDONLY);

	if (access(argv[argc], F_OK) == 0)
	{
		if (access(argv[argc], R_OK) == !0)
		{
			pipex->fdout = -1;
			return (0);
		}
		unlink(argv[argc]);
	}
	pipex->fdout = open(argv[argc], O_CREAT, 0644);
	return (0);
}
