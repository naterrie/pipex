/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:20:04 by naterrie          #+#    #+#             */
/*   Updated: 2023/05/11 14:39:26 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct pipex
{
	char	**cmd;
	char	*path_cmd;
	char	*path;
	int		i;
	int		fdin;
	int		fdout;
	int		pipefd[2];
}	t_pipex;

void	setpath(t_pipex	*pipex, char **env);

void	ft_exit(t_pipex *pipex);
int		check_space(char *str, t_pipex *pipex);
void	ft_dup(t_pipex *pipex, int fdin, int fdout);

int		try_to_access(t_pipex *pipex, char **path_list, int i);
void	end_process(t_pipex *pipex, pid_t pid);
int		set_absolute_path(t_pipex *pipex, char *arg);

#endif
