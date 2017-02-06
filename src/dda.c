/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:12:18 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 15:05:21 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	dda_util(t_env *env)
{
	if (env->wolf->ray_dir->x < 0)
	{
		env->wolf->step->x = -1;
		env->wolf->side_dist->x = (env->wolf->ray_pos->x
			- env->wolf->map_loc->x) * env->wolf->delta_dist->x;
	}
	else
	{
		env->wolf->step->x = 1;
		env->wolf->side_dist->x = (env->wolf->map_loc->x + 1.0
			- env->wolf->ray_pos->x) * env->wolf->delta_dist->x;
	}
	if (env->wolf->ray_dir->y < 0)
	{
		env->wolf->step->y = -1;
		env->wolf->side_dist->y = (env->wolf->ray_pos->y
			- env->wolf->map_loc->y) * env->wolf->delta_dist->y;
	}
	else
	{
		env->wolf->step->y = 1;
		env->wolf->side_dist->y = (env->wolf->map_loc->y + 1.0
			- env->wolf->ray_pos->y) * env->wolf->delta_dist->y;
	}
}

void	dda(t_env *env)
{
	dda_util(env);
	while (env->wolf->hit == 0)
	{
		if (env->wolf->side_dist->x < env->wolf->side_dist->y)
		{
			env->wolf->side_dist->x += env->wolf->delta_dist->x;
			env->wolf->map_loc->x += env->wolf->step->x;
			env->wolf->side = 0;
		}
		else
		{
			env->wolf->side_dist->y += env->wolf->delta_dist->y;
			env->wolf->map_loc->y += env->wolf->step->y;
			env->wolf->side = 1;
		}
		if (env->map[env->wolf->map_loc->x][env->wolf->map_loc->y] > 0)
			env->wolf->hit = 1;
	}
}
