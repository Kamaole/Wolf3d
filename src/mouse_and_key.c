#include "wolf.h"

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
