/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:19:50 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 14:20:47 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_wolf	*make_wolf(void)
{
	t_wolf *result;

	result = (t_wolf *)ft_memalloc(sizeof(t_wolf));
	result->pos = make_dvect(22.5, 12.5);
	result->dir = make_dvect(-1, 0);
	result->plane = make_dvect(0, .66);
	result->side_dist = make_dvect(0, 0);
	result->step = make_vect(0, 0);
	result->ray_pos = make_dvect(0, 0);
	result->ray_dir = make_dvect(0, 0);
	result->map_loc = make_vect(0, 0);
	result->delta_dist = make_dvect(0, 0);
	result->cur_floor = make_dvect(0, 0);
	result->floor_wall = make_dvect(0, 0);
	result->floor_tex = make_vect(0, 0);
	result->time = 0;
	result->time_tmp = 0;
	return (result);
}
