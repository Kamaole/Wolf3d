#include "wolf.h"
#include <stdio.h>

void 	set_speeds(t_env *env)
{
	env->wolf->move_speed = env->wolf->frame_time * 6.0;
	env->wolf->rot_speed = env->wolf->frame_time * 4.0;
}

void 	wolf_util(t_env *env)
{
	env->wolf->cameraX = 2 * env->wolf->x / (double)env->width - 1;
	env->wolf->ray_pos->x = env->wolf->pos->x;
	env->wolf->ray_pos->y = env->wolf->pos->y;
	env->wolf->ray_dir->x = env->wolf->dir->x
		+ env->wolf->plane->x * env->wolf->cameraX;
	env->wolf->ray_dir->y = env->wolf->dir->y
		+ env->wolf->plane->y * env->wolf->cameraX;
	env->wolf->map_loc->x = (int)env->wolf->ray_pos->x;
	env->wolf->map_loc->y = (int)env->wolf->ray_pos->y;
	env->wolf->delta_dist->x = sqrt(1 + (env->wolf->ray_dir->y
		* env->wolf->ray_dir->y) / (env->wolf->ray_dir->x
			* env->wolf->ray_dir->x));
	env->wolf->delta_dist->y = sqrt(1 + (env->wolf->ray_dir->x
		* env->wolf->ray_dir->x) / (env->wolf->ray_dir->y
			* env->wolf->ray_dir->y));
	env->wolf->hit = 0;
}

void 	move(t_env *env)
{
	if (env->keys->w)
	{
		printf("hi");
		if (!map_value((int)(env->wolf->pos->x + env->wolf->dir->x
			* env->wolf->move_speed), (int)(env->wolf->pos->y)))
			env->wolf->pos->x += env->wolf->dir->x * env->wolf->move_speed;
		if (!map_value((int)(env->wolf->pos->x), (int)(env->wolf->pos->y
			+ env->wolf->dir->y * env->wolf->move_speed)))
			env->wolf->pos->y += env->wolf->dir->y * env->wolf->move_speed;
	}
	if (env->keys->s)
	{
		if (!map_value((int)(env->wolf->pos->x - env->wolf->dir->x
			* env->wolf->move_speed), (int)(env->wolf->pos->y)))
			env->wolf->pos->x -= env->wolf->dir->x * env->wolf->move_speed;
		if (!map_value((int)(env->wolf->pos->x), (int)(env->wolf->pos->y
			- env->wolf->dir->y * env->wolf->move_speed)))
			env->wolf->pos->y -= env->wolf->dir->y * env->wolf->move_speed;
	}
	if (env->keys->a)
	{
		rot_fvect(env->wolf->dir, env->wolf->rot_speed);
		rot_fvect(env->wolf->plane, env->wolf->rot_speed);
	}
	if (env->keys->d)
	{
		rot_fvect(env->wolf->dir, -env->wolf->rot_speed);
		rot_fvect(env->wolf->plane, -env->wolf->rot_speed);
	}
}

void 	wolf(t_env *env)
{
	env->wolf->x = -1;
	while (++env->wolf->x < env->width)
	{
		wolf_util(env);
		dda(env);
		line_calc(env);
		draw_line(env);
		floor_cast(env);
	}
	move(env);
	draw_img(env);
	set_speeds(env);
}
