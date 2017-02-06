/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:22:28 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 14:23:30 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	rot_dvect(t_dvect *vect, double theta)
{
	double x_tmp;

	x_tmp = vect->x;
	vect->x = vect->x * cos(theta) - vect->y * sin(theta);
	vect->y = x_tmp * sin(theta) + vect->y * cos(theta);
}
