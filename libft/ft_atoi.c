/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 12:40:03 by rmatos            #+#    #+#             */
/*   Updated: 2016/09/29 17:50:00 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int neg;

	neg = 1;
	i = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\n' || *str == '\r')
		str++;
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		i = i * 10 + *str - '0';
		str++;
	}
	return (i * neg);
}