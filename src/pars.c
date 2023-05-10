/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:35 by naterrie          #+#    #+#             */
/*   Updated: 2023/05/10 15:41:27 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	try_to_access(t_pipex *pipex, char **path_list, int i)
{
	char	*temp;

	temp = ft_strjoin(path_list[i], "/");
	pipex->path_cmd = ft_strjoin(temp, pipex->cmd[0]);
	if (!pipex->path_cmd)
		return (1);
	free(temp);
	if (access(pipex->path_cmd, F_OK | X_OK) == 0)
	{
		free_str(path_list);
		return (0);
	}
	free(pipex->path_cmd);
	return (1);
}

int	set_absolute_path(t_pipex *pipex, char *arg)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_split(arg, ' ');
	pipex->path_cmd = ft_strdup(temp[i]);
	free_str(temp);
	temp = ft_split(arg, '/');
	while (temp[i])
		i++;
	i--;
	free_str(temp);
	i = 0;
	if (access(pipex->path_cmd, X_OK) == 0)
		return (0);
	free_str(pipex->cmd);
	free(pipex->path_cmd);
	write(1, "pipex: command not found\n", 25);
	return (2);
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
