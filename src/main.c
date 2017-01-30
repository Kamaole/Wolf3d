#include "wolf.h"
#include <stdio.h>
#include <time.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

void 	dda_util(t_env *env)
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

void 	dda(t_env *env)
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
		if (map_value(env->wolf->map_loc->x, env->wolf->map_loc->y) > 0)
			env->wolf->hit = 1;
	}
}

double get_wall_dist(t_env *env)
{
	if (env->wolf->side == 0)
		return ((env->wolf->map_loc->x - env->wolf->ray_pos->x
			+ (1 - env->wolf->step->x) / 2) / env->wolf->ray_dir->x);
	else
		return ((env->wolf->map_loc->y - env->wolf->ray_pos->y
			+ (1 - env->wolf->step->y) / 2) / env->wolf->ray_dir->y);
}

void 	texture_util(int **textures, int i, int j)
{
	int xorcolor;
	int ycolor;
	int xycolor;

	xorcolor = (i * 256 / 32) ^ (j * 256 / 32);
	ycolor = j * 256 / 32;
	xycolor = j * 128 / 32 + i * 128 / 32;
	textures[0][32 * j + i] = 65536 * 254 * ((i != j && i != 32 - j) ? 1 : 0);
	textures[1][32 * j + i] = xycolor + 256 * xycolor + 65536 * xycolor;
	textures[2][32 * j + i] = 256 * xycolor + 65536 * xycolor;
	textures[3][32 * j + i] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
	textures[4][32 * j + i] = 256 * xorcolor;
	textures[5][32 * j + i] = 65536 * 192 * ((i % 16 && j % 16) ? 1 : 0);
	textures[6][32 * j + i] = 65536 * ycolor;
	textures[7][32 * j + i] = 128 + 256 * 128 + 65536 * 128;
}

int		**make_textures(void)
{
	int i;
	int j;
	int **result;

	i = 0;
	result = (int **)ft_memalloc(sizeof(int *) * 8);
	while (i < 8)
		result[i++] = (int *)ft_memalloc(sizeof(int) * 4096);
	i = 0;
	while (i < 32)
	{
		j = 0;
		while (j < 32)
		{
			texture_util(result, i, j);
			j++;
		}
		i++;
	}
	return (result);
}

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

void 	draw_img(t_env *env)
{
	env->wolf->time_tmp = env->wolf->time;
	env->wolf->time = clock();
	env->wolf->frame_time = (env->wolf->time - env->wolf->time_tmp)
		/ CLOCKS_PER_SEC;
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->img_data->img, 0, 0);
	mlx_string_put(env->mlx, env->win, 0, 0, 0xFFFFFF,
		ft_itoa((int)(1 / env->wolf->frame_time)));
	free(env->img_data);
	env->img_data = make_img(env->mlx, env->width, env->height);
}

void 	set_speeds(t_env *env)
{
	printf("frame_time: %f\n", env->wolf->frame_time);
	env->wolf->move_speed = env->wolf->frame_time * 6.0;
	env->wolf->rot_speed = env->wolf->frame_time * 4.0;
}

void 	rot_fvect(t_fvect *vect, double theta)
{
	double x_tmp = vect->x;
	vect->x = vect->x * cos(theta) - vect->y * sin(theta);
	vect->y = x_tmp * sin(theta) + vect->y * cos(theta);
}

int		main(void)
{
	t_env *env = make_env(800, 600);
	wolf(env);
	mlx_hook(env->win, 2, 0, wolf_keys, env);
	mlx_hook(env->win, 6, 0, wolf_mouse, env);
	mlx_loop(env->mlx);
	return (0);
}
