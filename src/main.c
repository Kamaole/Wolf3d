#include "wolf.h"
#include <stdio.h>
#include <time.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

double get_wall_dist(t_env *env)
{
	if (env->wolf->side == 0)
		return ((env->wolf->map_loc->x - env->wolf->ray_pos->x
			+ (1 - env->wolf->step->x) / 2) / env->wolf->ray_dir->x);
	else
		return ((env->wolf->map_loc->y - env->wolf->ray_pos->y
			+ (1 - env->wolf->step->y) / 2) / env->wolf->ray_dir->y);
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

int		main(void)
{
	t_env *env = make_env(800, 600);
	wolf(env);
	mlx_hook(env->win, 2, 0, wolf_keys, env);
	mlx_hook(env->win, 6, 0, wolf_mouse, env);
	mlx_loop(env->mlx);
	return (0);
}
