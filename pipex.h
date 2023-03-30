/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:20:04 by naterrie          #+#    #+#             */
/*   Updated: 2023/03/30 17:47:03 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "./libft/libft.h"
#include <stdio.h>

typedef struct pipex
{

	char	*path;
}	t_pipex;

void	setpath(t_pipex	*pipex, char **env);

int		ft_checkfile(char **argv, int argc);

#endif