/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:35 by naterrie          #+#    #+#             */
/*   Updated: 2023/03/29 20:46:36 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	setpath(t_pipex	*pipex, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pipex->path = ft_substr(env[i], 5, ft_strlen(env[i]));
			pipex->pathint = i;
			return ;
		}
		i++;
	}
}

int	ft_checkfile(char **argv, int argc)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "ERROR\nInput file", 16);
		return (1);
	}
	close(fd);
	fd = open(argv[argc], O_RDONLY);
	if (fd < 0)
	{
		fd = open(argv[argc], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			write(1, "ERROR\nOutput file", 17);
		return (1);
	}
	close(fd);
	return (0);
}
