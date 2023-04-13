/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:20:04 by naterrie          #+#    #+#             */
/*   Updated: 2023/04/13 13:54:02 by naterrie         ###   ########lyon.fr   */
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
int		ft_checkfile(char **argv, int argc, t_pipex *pipex);

void	ft_exit(t_pipex *pipex);

#endif
