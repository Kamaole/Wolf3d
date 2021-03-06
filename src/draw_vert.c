/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:13:34 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 15:09:56 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double		get_wall_dist(t_env *env)
{
	if (env->wolf->side == 0)
		return ((env->wolf->map_loc->x - env->wolf->ray_pos->x
			+ (1 - env->wolf->step->x) / 2) / env->wolf->ray_dir->x);
	else
		return ((env->wolf->map_loc->y - env->wolf->ray_pos->y
			+ (1 - env->wolf->step->y) / 2) / env->wolf->ray_dir->y);
}

void		line_calc(t_env *env)
{
	env->wolf->wall_dist = get_wall_dist(env);
	env->wolf->line_len = (int)(env->height / env->wolf->wall_dist);
	env->wolf->draw_start = -env->wolf->line_len / 2 + env->height / 2;
	if (env->wolf->draw_start < 0)
		env->wolf->draw_start = 0;
	env->wolf->draw_end = env->wolf->line_len / 2 + env->height / 2;
	if (env->wolf->draw_end >= env->height)
		env->wolf->draw_end = env->height - 1;
	env->wolf->line = make_line(env->wolf->x, env->wolf->draw_start,
		env->wolf->x, env->wolf->draw_end);
	env->wolf->tex_num = env->map[env->wolf->map_loc->x][env->wolf->map_loc->y]
		- 1;
	if (env->wolf->side == 0)
		env->wolf->wall_x = env->wolf->ray_pos->y
			+ env->wolf->wall_dist * env->wolf->ray_dir->y;
	else
		env->wolf->wall_x = env->wolf->ray_pos->x
			+ env->wolf->wall_dist * env->wolf->ray_dir->x;
	env->wolf->wall_x -= floor(env->wolf->wall_x);
	env->wolf->tex_x = (int)(env->wolf->wall_x * 32.0);
	if (env->wolf->side == 0 && env->wolf->ray_dir->x > 0)
		env->wolf->tex_x = 32 - env->wolf->tex_x - 1;
	if (env->wolf->side == 1 && env->wolf->ray_dir->y < 0)
		env->wolf->tex_x = 32 - env->wolf->tex_x - 1;
	env->wolf->y = env->wolf->draw_start - 1;
}

void		draw_line(t_env *env)
{
	int d;
	int tex_y;
	int color;

	while (++env->wolf->y < env->wolf->draw_end)
	{
		d = env->wolf->y * 256 - env->height * 128 + env->wolf->line_len * 128;
		tex_y = ((d * 32) / env->wolf->line_len) / 256;
		color = env->textures[env->wolf->tex_num]
			[32 * tex_y + env->wolf->tex_x];
		if (env->wolf->side == 1)
			color = (color >> 1) & 8355711;
		pixel_to_img(env->img_data, env->wolf->x, env->wolf->y, color);
	}
}
