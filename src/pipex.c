/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:36:34 by naterrie          #+#    #+#             */
/*   Updated: 2023/03/30 17:46:28 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_exit(t_pipex *pipex)
{
	free(pipex->path);
}

void	process_exec(char *cmd, char **argv, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (!pid)
		execve(cmd, argv, env);
	else
		waitpid(pid, NULL, 0);
}

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

char	*get_path(char **env, char **argv, int a, t_pipex *pipex)
{
	char	**path_list;
	char	*cmd;
	char	*temp;
	int		i;


	setpath(pipex, env);
	path_list = ft_split(pipex->path, ':');
	free(pipex->path);
	i = 0;
	while (path_list[i] != NULL)
	{
		temp = ft_strjoin(path_list[i], "/");
		cmd = ft_strjoin(temp, argv[a]);
		free(temp);
		if (access(cmd, X_OK) == 0)
		{
			free_str(path_list);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	free_str(path_list);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	char	*cmd;

	if (argc < 5)
		return (1);
	if (ft_checkfile(argv, argc - 1) == 1)
		return (1);
	cmd = get_path(env, argv, 2, &pipex);
	process_exec(cmd, argv, env);
	free(cmd);
	return (0);
}
