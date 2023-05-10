/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:29:40 by naterrie          #+#    #+#             */
/*   Updated: 2023/05/10 13:53:36 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*new;
	int		i;

	if (!lst)
		return (0);
	i = 0;
	new = lst;
	while (new)
	{
		new = new->next;
		i++;
	}
	return (i);
}
