/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:36:34 by naterrie          #+#    #+#             */
/*   Updated: 2023/04/05 16:30:36 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <stdio.h>

void	ft_exit(t_pipex *pipex, int fdout, int fdin, int exitcode)
{
	free(pipex->path_cmd);
	free_str(pipex->cmd);
	close(fdin);
	close(fdout);
	if (exitcode == 1)
		exit(0);
}

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

void	exec_cmd(t_pipex *pipex, char **env)
{
	pid_t	pid;

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
}

void	process_exec(t_pipex *pipex, char **argv, char **env, int i)
{
	int		fdin;
	int		fdout;
	int		the_pipe[2];

	pipe(the_pipe);
	fdout = open(argv[4], O_WRONLY);
	fdin = open(argv[1], O_RDONLY);
	if (get_path(env, argv, pipex, i) == 1)
	{
		free_str(pipex->cmd);
		return ;
	}
	dup2(fdin, 0);
	dup2(the_pipe[0], 1);
	exec_cmd(pipex, env);
	close(the_pipe[0]);
	close(the_pipe[1]);
	ft_exit(pipex, fdin, fdout, 0);
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
	close(1);
	close(0);
	close(2);
	return (0);
}
