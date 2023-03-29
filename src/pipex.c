/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:36:34 by naterrie          #+#    #+#             */
/*   Updated: 2023/03/29 03:58:56 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < 5)
		return (1);
	if (ft_checkfile(argv) == 1)
		return (1);
	setpath(&pipex, env);
	return (0);
}
