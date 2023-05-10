/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:22:39 by naterrie          #+#    #+#             */
/*   Updated: 2023/05/10 17:40:02 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	end_process(t_pipex *pipex, pid_t pid)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	close(0);
	if (pid != 0)
	{
		waitpid(pid - 1, NULL, 0);
		waitpid(pid, NULL, 0);
	}
}

int	check_space(char *str, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 0)
	{
		write(1, "pipex: command not found\n", 25);
		free_str(pipex->cmd);
		return (1);
	}
	return (0);
}

void	ft_dup(t_pipex *pipex, int fdin, int fdout)
{
	if (dup2(fdin, fdout) != -1)
		return ;
	if (pipex->cmd != NULL)
		free_str(pipex->cmd);
	if (pipex->path_cmd != NULL)
		free(pipex->path_cmd);
	if (pipex->fdin != -1)
		close(pipex->fdin);
	if (pipex->fdout != -1)
		close(pipex->fdout);
	exit(1);
}

void	ft_exit(t_pipex *pipex)
{
	if (pipex->fdin != -1)
		close(pipex->fdin);
	if (pipex->fdout != -1)
		close(pipex->fdout);
	exit(1);
}
