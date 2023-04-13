/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:35 by naterrie          #+#    #+#             */
/*   Updated: 2023/04/12 17:06:41 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <stdio.h>

void	ft_exit(t_pipex *pipex)
{
	close(1);
	close(0);
	close(2);
	close(pipex->fdin);
	close(pipex->fdout);
	exit(0);
}

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
	pipex->fdout = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (0);
}
