#include "wolf.h"

void 	move_camera(int keycode, t_env *env)
{
	if (keycode == 13)
	{
		if (!map_value((int)(env->wolf->pos->x + env->wolf->dir->x
			* env->wolf->move_speed), (int)(env->wolf->pos->y)))
			env->wolf->pos->x += env->wolf->dir->x * env->wolf->move_speed;
		if (!map_value((int)(env->wolf->pos->x), (int)(env->wolf->pos->y
			+ env->wolf->dir->y * env->wolf->move_speed)))
			env->wolf->pos->y += env->wolf->dir->y * env->wolf->move_speed;
	}
	if (keycode == 1)
	{
		if (!map_value((int)(env->wolf->pos->x - env->wolf->dir->x
			* env->wolf->move_speed), (int)(env->wolf->pos->y)))
			env->wolf->pos->x -= env->wolf->dir->x * env->wolf->move_speed;
		if (!map_value((int)(env->wolf->pos->x), (int)(env->wolf->pos->y
			- env->wolf->dir->y * env->wolf->move_speed)))
			env->wolf->pos->y -= env->wolf->dir->y * env->wolf->move_speed;
	}
}

void 	rotate_camera(int keycode, t_env *env)
{
	if (keycode == 2 || keycode == 0)
	{
		rot_fvect(env->wolf->dir,
			((keycode == 2) ? -env->wolf->rot_speed : env->wolf->rot_speed));
		rot_fvect(env->wolf->plane,
			((keycode == 2) ? -env->wolf->rot_speed : env->wolf->rot_speed));
	}
}

int 	wolf_keys(int keycode, t_env *env)
{
	move_camera(keycode, env);
	rotate_camera(keycode, env);
	if (keycode == 53)
		exit(0);
	wolf(env);
	return (0);
}

int		wolf_mouse(int x, int y, t_env *env)
{
	rot_fvect(env->wolf->dir,
		((x > env->last_x) ? -env->wolf->rot_speed : env->wolf->rot_speed));
	rot_fvect(env->wolf->plane,
		((x > env->last_x) ? -env->wolf->rot_speed : env->wolf->rot_speed));
	env->last_x = x;
	y = 0;
	wolf(env);
	return (0);
}
