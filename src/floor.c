/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:15:21 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 14:15:59 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	floor_calc(t_env *env)
{
	if (env->wolf->side == 0 && env->wolf->ray_dir->x > 0)
	{
		env->wolf->floor_wall->x = env->wolf->map_loc->x;
		env->wolf->floor_wall->y = env->wolf->map_loc->y + env->wolf->wall_x;
	}
	else if (env->wolf->side == 0 && env->wolf->ray_dir->x < 0)
	{
		env->wolf->floor_wall->x = env->wolf->map_loc->x + 1.0;
		env->wolf->floor_wall->y = env->wolf->map_loc->y + env->wolf->wall_x;
	}
	else if (env->wolf->side == 1 && env->wolf->ray_dir->y > 0)
	{
		env->wolf->floor_wall->x = env->wolf->map_loc->x + env->wolf->wall_x;
		env->wolf->floor_wall->y = env->wolf->map_loc->y;
	}
	else
	{
		env->wolf->floor_wall->x = env->wolf->map_loc->x + env->wolf->wall_x;
		env->wolf->floor_wall->y = env->wolf->map_loc->y + 1.0;
	}
	env->wolf->dist_wall = env->wolf->wall_dist;
	env->wolf->dist_player = 0.0;
	if (env->wolf->draw_end < 0)
		env->wolf->draw_end = env->height;
	env->wolf->y = env->wolf->draw_end;
}

void	floor_cast(t_env *env)
{
	floor_calc(env);
	while (++env->wolf->y < env->height)
	{
		env->wolf->current_dist = env->height
			/ (2.0 * env->wolf->y - env->height);
		env->wolf->weight = (env->wolf->current_dist - env->wolf->dist_player)
			/ (env->wolf->dist_wall - env->wolf->dist_player);
		env->wolf->cur_floor->x = env->wolf->weight * env->wolf->floor_wall->x
			+ (1.0 - env->wolf->weight) * env->wolf->pos->x;
		env->wolf->cur_floor->y = env->wolf->weight * env->wolf->floor_wall->y
			+ (1.0 - env->wolf->weight) * env->wolf->pos->y;
		env->wolf->floor_tex->x = (int)(env->wolf->cur_floor->x * 32) % 32;
		env->wolf->floor_tex->y = (int)(env->wolf->cur_floor->y * 32) % 32;
		env->wolf->color = env->textures[4][32 * env->wolf->floor_tex->y
			+ env->wolf->floor_tex->x] >> 1 & 8355711;
		pixel_to_img(env->img_data, env->wolf->x,
			env->height - env->wolf->y, env->wolf->color);
		env->wolf->color = env->textures[3][32 * env->wolf->floor_tex->y
			+ env->wolf->floor_tex->x];
		pixel_to_img(env->img_data, env->wolf->x, env->wolf->y,
			env->wolf->color);
	}
}
