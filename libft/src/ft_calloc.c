/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 00:47:51 by naterrie          #+#    #+#             */
/*   Updated: 2023/05/10 13:53:11 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	if (size > 0 && count >= SIZE_MAX / size)
		return (NULL);
	str = malloc((sizeof(char) * (count * size)));
	if (!str)
		return (NULL);
	ft_bzero(str, size * count);
	return ((void *)str);
}
