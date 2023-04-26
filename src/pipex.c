/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:20:00 by naterrie          #+#    #+#             */
/*   Updated: 2023/04/26 17:30:52 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_path(char **env, char **argv, t_pipex *pipex, int j)
{
	char	**path_list;
	int		i;

	i = 0;
	pipex->cmd = ft_split(argv[j], ' ');
	if (check_space(argv[j], pipex) == 1)
		return (2);
	if (ft_strlen(argv[j]) == 0 || ft_strchr(pipex->cmd[0], '/') != NULL)
		return (set_absolute_path(pipex, argv[j]));
	setpath(pipex, env);
	path_list = ft_split(pipex->path, ':');
	free(pipex->path);
	while (path_list[i++])
		if (try_to_access(pipex, path_list, i) == 0)
			return (0);
	write(1, "pipex: command not found\n", 25);
	return (free_str(path_list), 1);
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
		free(pipex->path_cmd);
		free_str(pipex->cmd);
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
	int		k;

	j = 1;
	pid = 0;
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
		k = get_path(env, args, pipex, i);
		if (k == 0)
			pid = child_process(pipex, env, i);
		else if (k == 1)
			free_str(pipex->cmd);
		i++;
	}
	end_process(pipex, pid);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		write (1, "pipex : wrong number of arguments\n", 35);
		return (1);
	}
	pipex.fdin = open(argv[1], O_RDONLY);
	pipex.fdout = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex.fdin == -1)
		write(1, "pipex : input file invalid\n", 27);
	if (pipex.fdout == -1)
		write(1, "pipex : output file invalid\n", 28);
	if (pipex.fdin != -1 || pipex.fdout != -1)
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
