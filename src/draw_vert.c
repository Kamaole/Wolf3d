#include "wolf.h"

void 	line_calc(t_env *env)
{
	env->wolf->perpWallDist = get_wall_dist(env);
	env->wolf->line_len = (int)(env->height / env->wolf->perpWallDist);
	env->wolf->draw_start = -env->wolf->line_len / 2 + env->height / 2;
	if (env->wolf->draw_start < 0)
		env->wolf->draw_start = 0;
	env->wolf->draw_end = env->wolf->line_len / 2 + env->height / 2;
	if (env->wolf->draw_end >= env->height)
		env->wolf->draw_end = env->height - 1;
	env->wolf->line = make_line(env->wolf->x, env->wolf->draw_start,
		env->wolf->x, env->wolf->draw_end);
	env->wolf->tex_num = map_value(env->wolf->map_loc->x, env->wolf->map_loc->y)
		- 1;
	if (env->wolf->side == 0)
		env->wolf->wall_x = env->wolf->ray_pos->y
			+ env->wolf->perpWallDist * env->wolf->ray_dir->y;
	else
		env->wolf->wall_x = env->wolf->ray_pos->x
			+ env->wolf->perpWallDist * env->wolf->ray_dir->x;
	env->wolf->wall_x -= floor(env->wolf->wall_x);
	env->wolf->tex_x = (int)(env->wolf->wall_x * 32.0);
	if (env->wolf->side == 0 && env->wolf->ray_dir->x > 0)
		env->wolf->tex_x = 32 - env->wolf->tex_x - 1;
	if (env->wolf->side == 1 && env->wolf->ray_dir->y < 0)
		env->wolf->tex_x = 32 - env->wolf->tex_x - 1;
	env->wolf->y = env->wolf->draw_start - 1;
}

void 	draw_line(t_env *env)
{
	while (++env->wolf->y < env->wolf->draw_end)
	{
		int d = env->wolf->y * 256 - env->height * 128 + env->wolf->line_len * 128;
		int texY = ((d * 32) / env->wolf->line_len) / 256;
		int color = env->textures[env->wolf->tex_num][32 * texY + env->wolf->tex_x];
		if (env->wolf->side == 1)
			color = (color >> 1) & 8355711;
		pixel_to_img(env->img_data, env->wolf->x, env->wolf->y, color);
	}
}