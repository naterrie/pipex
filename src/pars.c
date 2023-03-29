/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:35 by naterrie          #+#    #+#             */
/*   Updated: 2023/03/29 05:09:08 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	setpath(t_pipex	*pipex, char **env)
{
	int	i;

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

int	ft_checkfile(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "ERROR\n", 6);
		return (1);
	}
	close(fd);
	fd = open(argv[4], O_CREAT | O_WRONLY);
	if (fd < 0)
	{
		write(1, "ERROR\nNo Output file", 15);
		return (1);
	}
	close(fd);
	return (0);
}
