#include "wolf.h"
#include <stdio.h>
#include <time.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int		main(void)
{
	t_env *env = make_env(800, 600);
	wolf(env);
	mlx_hook(env->win, 2, 0, wolf_keys, env);
	mlx_hook(env->win, 6, 0, wolf_mouse, env);
	mlx_loop(env->mlx);
	return (0);
}
