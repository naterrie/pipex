/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:52:39 by naterrie          #+#    #+#             */
/*   Updated: 2022/11/25 14:17:27 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sign(int nb)
{
	if (nb == -1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	nbr;
	int		neg;

	i = 0;
	nbr = 0;
	neg = -1;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
		i++;
	if (str[i] != '\0' && str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (nbr != ((nbr * 10) + (str[i] - '0')) / 10)
			return (sign(neg));
		nbr = (nbr * 10) + (str[i++] - '0');
	}
	if (neg == 1)
		return (-nbr);
	return (nbr);
}
