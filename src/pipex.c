/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:36:34 by naterrie          #+#    #+#             */
/*   Updated: 2023/03/29 20:53:15 by naterrie         ###   ########lyon.fr   */
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

void	execute_cmd(t_pipex *pipex, char **argv, char **env, int argc)
{
	char	**path_list;
	char	*cmd;
	int		i;

	(void)argc;
	(void)env;
	path_list = ft_split(pipex->path, ':');
	i = 0;
	while (path_list[i] != NULL)
	{
		if (access(path_list[i], X_OK) == 0)
		{
			cmd = ft_strjoin(path_list[i], "/");
			cmd = ft_strjoin(cmd, argv[2]);
			free_str(path_list);
			process_exec(cmd, argv, env);
			free(cmd);
			return ;
		}
		i++;
	}
	free_str(path_list);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < 5)
		return (1);
	if (ft_checkfile(argv, argc - 1) == 1)
		return (1);
	setpath(&pipex, env);
	execute_cmd(&pipex, argv, env, argc);
	free(pipex.path);
	return (0);
}
