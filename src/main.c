#include "wolf.h"
#include <stdio.h>
#include <time.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int 	key_pressed(int keycode, t_env *env)
{
	if (keycode == 13 && !env->keys->w)
		env->keys->w = 1;
	if (keycode == 0 && !env->keys->a)
		env->keys->a = 1;
	if (keycode == 1 && !env->keys->s)
		env->keys->s = 1;
	if (keycode == 2 && !env->keys->d)
		env->keys->d = 1;
	wolf(env);
	return (keycode);
}

int 	key_released(int keycode, t_env *env)
{
	if (keycode == 13 && env->keys->w)
		env->keys->w = 0;
	if (keycode == 0 && env->keys->a)
		env->keys->a = 0;
	if (keycode == 1 && env->keys->s)
		env->keys->s = 0;
	if (keycode == 2 && env->keys->d)
		env->keys->d = 0;
	printf("keycode: %i\n", keycode);
	wolf(env);
	return (keycode);
}

int		loop(t_env *env)
{
	wolf(env);
	return (0);
}

int		main(void)
{
	t_env *env = make_env(800, 600);
	wolf(env);
	// mlx_hook(env->win, 2, 0, wolf_keys, env);
	mlx_hook(env->win, 6, 0, wolf_mouse, env);
	mlx_hook(env->win, 2, 0, key_pressed, env);
	mlx_hook(env->win, 3, 0, key_released, env);
	mlx_loop_hook(env->mlx, loop, env);
	mlx_loop(env->mlx);
	return (0);
}
