/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rework.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:20:00 by naterrie          #+#    #+#             */
/*   Updated: 2023/04/10 16:21:57 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_path(char **env, char **argv, t_pipex *pipex, int j)
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
			return (0);
		}
		free(pipex->path_cmd);
		i++;
	}
	write(1, "pipex: command not found\n", 25);
	free_str(path_list);
	return (1);
}

pid_t	child_process(t_pipex *pipex, char **args, char **env, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	(void)i;
	(void)args;
	if (!pid)
	{
		execve(pipex->path_cmd, pipex->cmd, env);
		exit(0);
	}
	return (pid);
}

void	process_exec(t_pipex *pipex, char **args, char **env, int i)
{
	pid_t	pid;
	int		j;

	j = 1;
	if (pipex->fdin == -1)
		i++;
	else
		dup2(pipex->fdin, 0);
	if (pipex->fdout == -1)
		j++;
	else
		dup2(pipex->fdout, 1);
	while (args[i + j])
	{
		if (get_path(env, args, pipex, i) == 0)
			pid = child_process(pipex, args, env, i);
		i++;
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	pipex.numbarg = argc;
	ft_checkfile(argv, argc - 1, &pipex);
	if (argc < 5)
		return (1);
	process_exec(&pipex, argv, env, argc - 3);
	close(1);
	close(0);
	close(2);
	return (0);
}
