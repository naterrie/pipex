/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:36:34 by naterrie          #+#    #+#             */
/*   Updated: 2023/04/03 17:08:45 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	get_path(char **env, char **argv, t_pipex *pipex, int j)
{
	char	**path_list;
	char	*temp;
	int		i;

	setpath(pipex, env);
	path_list = ft_split(pipex->path, ':');
	free(pipex->path);
	i = 0;
	pipex->cmd = ft_split(argv[j], ' ');
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		pipex->path_cmd = ft_strjoin(temp, pipex->cmd[0]);
		free(temp);
		if (access(pipex->path_cmd, X_OK) == 0)
		{
			free_str(path_list);
			return ;
		}
		free(pipex->path_cmd);
		i++;
	}
	free_str(path_list);
}

void	process_exec(t_pipex *pipex, char **argv, char **env, int i)
{
	pid_t	pid;
	int		fd;
	int		fdout;

	fdout = open(argv[4], O_WRONLY);
	fd = open(argv[1], O_RDONLY);
	get_path(env, argv, pipex, i);
	dup2(fd, 0);
	dup2(fdout, 1);
	pid = fork();
	if (pid == -1)
		return ;
	if (!pid)
	{
		execve(pipex->path_cmd, pipex->cmd, env);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
	free(pipex->path_cmd);
	free_str(pipex->cmd);
	close(fd);
	close(fdout);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		file;

	if (argc < 5)
		return (1);
	file = ft_checkfile(argv, argc - 1);
	if (file == 0)
	{
		process_exec(&pipex, argv, env, 2);
		process_exec(&pipex, argv, env, 3);
	}
	else if (file == 1)
		process_exec(&pipex, argv, env, 3);
	else if (file == 2)
		process_exec(&pipex, argv, env, 2);
	return (0);
}
