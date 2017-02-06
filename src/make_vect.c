/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_vect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:11:44 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 14:19:45 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_vect		*make_vect(int x, int y)
{
	t_vect *result;

	result = (t_vect *)ft_memalloc(sizeof(t_vect));
	result->x = x;
	result->y = y;
	return (result);
}

t_dvect		*make_dvect(double x, double y)
{
	t_dvect *result;

	result = (t_dvect *)ft_memalloc(sizeof(t_dvect));
	result->x = x;
	result->y = y;
	return (result);
}
