/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:20:00 by naterrie          #+#    #+#             */
/*   Updated: 2023/04/13 14:46:16 by naterrie         ###   ########lyon.fr   */
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

void	change_fd(t_pipex *pipex)
{
	close(pipex->pipefd[1]);
	dup2(pipex->pipefd[0], 0);
	close(pipex->pipefd[0]);
	dup2(pipex->fdout, 1);
	if (pipex->fdout != 1)
		close(pipex->fdout);
}

pid_t	child_process(t_pipex *pipex, char **env, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	if (!pid)
	{
		if (i == 2)
		{
			close(pipex->pipefd[0]);
			dup2(pipex->pipefd[1], 1);
			close(pipex->pipefd[1]);
		}
		else
			change_fd(pipex);
		execve(pipex->path_cmd, pipex->cmd, env);
		exit(1);
	}
	free(pipex->path_cmd);
	free_str(pipex->cmd);
	return (pid);
}

void	process_exec(t_pipex *pipex, char **args, char **env, int i)
{
	pid_t	pid;
	int		j;

	j = 1;
	if (pipe(pipex->pipefd) == -1)
		exit(0);
	if (pipex->fdin == -1)
		i++;
	else
		dup2(pipex->fdin, 0);
	if (pipex->fdout == -1)
		j++;
	while (args[i + j])
	{
		if (get_path(env, args, pipex, i) == 0)
			pid = child_process(pipex, env, i);
		else
			free_str(pipex->cmd);
		i++;
	}
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	close(0);
	waitpid(pid -1, NULL, 0);
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		return (1);
	ft_checkfile(argv, argc, &pipex);
	if (pipex.fdin != -1 && pipex.fdout != -1)
	{
		process_exec(&pipex, argv, env, argc - 3);
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
	}
	if (pipex.fdin != -1)
		close(pipex.fdin);
	if (pipex.fdout != -1)
		close (pipex.fdout);
}
