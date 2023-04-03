/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:35 by naterrie          #+#    #+#             */
/*   Updated: 2023/04/03 15:32:35 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	setpath(t_pipex	*pipex, char **env)
{
	int		i;

	i = 0;
	if (!env)
		exit(1);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pipex->path = ft_substr(env[i], 5, ft_strlen(env[i]));
			return ;
		}
		i++;
	}
}

int	ft_checkfile(char **argv, int argc)
{
	int	fd;
	int	ret;

	ret = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "ERROR\nInput file", 16);
		ret += 1;
	}
	close(fd);
	fd = open(argv[argc], O_RDONLY);
	if (fd < 0)
	{
		fd = open(argv[argc], O_CREAT, 0644);
		if (fd < 0)
		{
			write(1, "ERROR\nOutput file", 17);
			ret += 2;
		}
	}
	close(fd);
	return (ret);
}
