#include "wolf.h"

void 	floor_calc(t_env *env)
{
	if (env->wolf->side == 0 && env->wolf->ray_dir->x > 0)
	{
		env->wolf->floorXWall = env->wolf->map_loc->x;
		env->wolf->floorYWall = env->wolf->map_loc->y + env->wolf->wall_x;
	}
	else if (env->wolf->side == 0 && env->wolf->ray_dir->x < 0)
	{
		env->wolf->floorXWall = env->wolf->map_loc->x + 1.0;
		env->wolf->floorYWall = env->wolf->map_loc->y + env->wolf->wall_x;
	}
	else if (env->wolf->side == 1 && env->wolf->ray_dir->y > 0)
	{
		env->wolf->floorXWall = env->wolf->map_loc->x + env->wolf->wall_x;
		env->wolf->floorYWall = env->wolf->map_loc->y;
	}
	else
	{
		env->wolf->floorXWall = env->wolf->map_loc->x + env->wolf->wall_x;
		env->wolf->floorYWall = env->wolf->map_loc->y + 1.0;
	}
	env->wolf->distWall = env->wolf->perpWallDist;
	env->wolf->distPlayer = 0.0;
	if (env->wolf->draw_end < 0)
		env->wolf->draw_end = env->height;
	env->wolf->y = env->wolf->draw_end;
}

void 	floor_cast(t_env *env)
{
	floor_calc(env);
	while (++env->wolf->y < env->height)
	{
		env->wolf->currentDist = env->height
			/ (2.0 * env->wolf->y - env->height);
		env->wolf->weight = (env->wolf->currentDist - env->wolf->distPlayer)
			/ (env->wolf->distWall - env->wolf->distPlayer);
		env->wolf->currentFloorX = env->wolf->weight * env->wolf->floorXWall
			+ (1.0 - env->wolf->weight) * env->wolf->pos->x;
		env->wolf->currentFloorY = env->wolf->weight * env->wolf->floorYWall
			+ (1.0 - env->wolf->weight) * env->wolf->pos->y;
		env->wolf->floorTexX = (int)(env->wolf->currentFloorX * 32) % 32;
		env->wolf->floorTexY = (int)(env->wolf->currentFloorY * 32) % 32;
		env->wolf->color = env->textures[4][32 * env->wolf->floorTexY
			+ env->wolf->floorTexX] >> 1 & 8355711;
		pixel_to_img(env->img_data, env->wolf->x,
			env->height - env->wolf->y, env->wolf->color);
		env->wolf->color = env->textures[3][32 * env->wolf->floorTexY
		 	+ env->wolf->floorTexX];
		pixel_to_img(env->img_data, env->wolf->x, env->wolf->y,
			env->wolf->color);
	}
}
