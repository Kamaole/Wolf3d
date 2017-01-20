#include "wolf.h"
#include <stdio.h>
#include <time.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int worldMap[MAP_WIDTH][MAP_HEIGHT]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int colors[5] = {0xFF0000, 0x00FF00, 0xFF00FF, 0xFFFF00, 0x00BFFF};

void 	wolfed_util(t_env *env)
{
	env->wolf->x = 0;
	while (env->wolf->x < env->width)
	{
		env->wolf->cameraX = 2 * env->wolf->x / (double)env->width - 1;
		env->wolf->rayPosX = env->wolf->posX;
		env->wolf->rayPosY = env->wolf->posY;
		env->wolf->rayDirX = env->wolf->dirX + env->wolf->planeX * env->wolf->cameraX;
		env->wolf->rayDirY = env->wolf->dirY + env->wolf->planeY * env->wolf->cameraX;
		env->wolf->mapX = (int)env->wolf->rayPosX;
		env->wolf->mapY = (int)env->wolf->rayPosY;
		env->wolf->deltaDistX = sqrt(1 + (env->wolf->rayDirY * env->wolf->rayDirY) / (env->wolf->rayDirX * env->wolf->rayDirX));
		env->wolf->deltaDistY = sqrt(1 + (env->wolf->rayDirX * env->wolf->rayDirX) / (env->wolf->rayDirY * env->wolf->rayDirY));
		env->wolf->hit = 0;
		if (env->wolf->rayDirX < 0)
		{
			env->wolf->stepX = -1;
			env->wolf->sideDistX = (env->wolf->rayPosX - env->wolf->mapX) * env->wolf->deltaDistX;
		}
		else
		{
			env->wolf->stepX = 1;
			env->wolf->sideDistX = (env->wolf->mapX + 1.0 - env->wolf->rayPosX) * env->wolf->deltaDistX;
		}
		if (env->wolf->rayDirY < 0)
		{
			env->wolf->stepY = -1;
			env->wolf->sideDistY = (env->wolf->rayPosY - env->wolf->mapY) * env->wolf->deltaDistY;
		}
		else
		{
			env->wolf->stepY = 1;
			env->wolf->sideDistY = (env->wolf->mapY + 1.0 - env->wolf->rayPosY) * env->wolf->deltaDistY;
		}
		while (env->wolf->hit == 0)
		{
			if (env->wolf->sideDistX < env->wolf->sideDistY)
			{
				env->wolf->sideDistX += env->wolf->deltaDistX;
				env->wolf->mapX += env->wolf->stepX;
				env->wolf->side = 0;
			}
			else
			{
				env->wolf->sideDistY += env->wolf->deltaDistY;
				env->wolf->mapY += env->wolf->stepY;
				env->wolf->side = 1;
			}
			if (worldMap[env->wolf->mapX][env->wolf->mapY] > 0)
				env->wolf->hit = 1;
		}
		if (env->wolf->side == 0)
			env->wolf->perpWallDist = (env->wolf->mapX - env->wolf->rayPosX + (1 - env->wolf->stepX) / 2) / env->wolf->rayDirX;
		else
			env->wolf->perpWallDist = (env->wolf->mapY - env->wolf->rayPosY + (1 - env->wolf->stepY) / 2) / env->wolf->rayDirY;
		env->wolf->line_len = (int)(env->height / env->wolf->perpWallDist);
		env->wolf->draw_start = -env->wolf->line_len / 2 + env->height / 2;
		if (env->wolf->draw_start < 0)
			env->wolf->draw_start = 0;
		env->wolf->draw_end = env->wolf->line_len / 2 + env->height / 2;
		if (env->wolf->draw_end >= env->height)
			env->wolf->draw_end = env->height - 1;
		env->wolf->line = make_line(env->wolf->x, env->wolf->draw_start, env->wolf->x, env->wolf->draw_end);
		if (env->wolf->side == 1)
			put_line(env->img_data, env->wolf->line, colors[worldMap[env->wolf->mapX][env->wolf->mapY]] / 2);
		else
			put_line(env->img_data, env->wolf->line, colors[worldMap[env->wolf->mapX][env->wolf->mapY]]);
		env->wolf->x += 1;
	}
	env->wolf->time_tmp = env->wolf->time;
	env->wolf->time = clock();
	env->wolf->frame_time = (env->wolf->time - env->wolf->time_tmp) / CLOCKS_PER_SEC;
	printf("frame_time: %f\n", env->wolf->frame_time);
	printf("fps: %f\n", 1.0 / env->wolf->frame_time);
	env->wolf->move_speed = env->wolf->frame_time * 8.0;
	env->wolf->rot_speed = env->wolf->frame_time * 3.0;
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->img_data->img, 0, 0);
	env->img_data = make_img(env->mlx, env->width, env->height);
}

int 	wolf_keys(int keycode, t_env *env)
{
	if (keycode == 13)
	{
		if (!worldMap[(int)(env->wolf->posX + env->wolf->dirX * env->wolf->move_speed)][(int)(env->wolf->posY)])
			env->wolf->posX += env->wolf->dirX * env->wolf->move_speed;
		if (!worldMap[(int)(env->wolf->posX)][(int)(env->wolf->posY + env->wolf->dirY * env->wolf->move_speed)])
			env->wolf->posY += env->wolf->dirY * env->wolf->move_speed;
	}
	if (keycode == 1)
	{
		if (!worldMap[(int)(env->wolf->posX + env->wolf->dirX * env->wolf->move_speed)][(int)(env->wolf->posY)])
			env->wolf->posX -= env->wolf->dirX * env->wolf->move_speed;
		if (!worldMap[(int)(env->wolf->posX)][(int)(env->wolf->posY + env->wolf->dirY * env->wolf->move_speed)])
			env->wolf->posY -= env->wolf->dirY * env->wolf->move_speed;
	}
	if (keycode == 2)
	{
		double oldDirX = env->wolf->dirX;
		env->wolf->dirX = env->wolf->dirX * cos(-env->wolf->rot_speed) - env->wolf->dirY * sin(-env->wolf->rot_speed);
		env->wolf->dirY = oldDirX * sin(-env->wolf->rot_speed) + env->wolf->dirY * cos(-env->wolf->rot_speed);
		double oldPlaneX = env->wolf->planeX;
		env->wolf->planeX = env->wolf->planeX * cos(-env->wolf->rot_speed) - env->wolf->planeY * sin(-env->wolf->rot_speed);
		env->wolf->planeY = oldPlaneX * sin(-env->wolf->rot_speed) + env->wolf->planeY * cos(-env->wolf->rot_speed);
	}
	if (keycode == 0)
	{
		double oldDirX = env->wolf->dirX;
		env->wolf->dirX = env->wolf->dirX * cos(env->wolf->rot_speed) - env->wolf->dirY * sin(env->wolf->rot_speed);
		env->wolf->dirY = oldDirX * sin(env->wolf->rot_speed) + env->wolf->dirY * cos(env->wolf->rot_speed);
		double oldPlaneX = env->wolf->planeX;
		env->wolf->planeX = env->wolf->planeX * cos(env->wolf->rot_speed) - env->wolf->planeY * sin(env->wolf->rot_speed);
		env->wolf->planeY = oldPlaneX * sin(env->wolf->rot_speed) + env->wolf->planeY * cos(env->wolf->rot_speed);
	}
	wolfed_util(env);
	printf("keycode: %i\n", keycode);
	return (0);
}

void 	wolfed(t_env *env)
{
	wolfed_util(env);
}

int		main(void)
{
	clock_t launch = clock();
	t_env *env = make_env(1000, 1000);
	wolfed(env);
	clock_t done = clock();
	double diff = (done - launch) / CLOCKS_PER_SEC;
	printf("%f\n", diff);
	mlx_hook(env->win, 2, 0, wolf_keys, env);
	mlx_loop(env->mlx);
	return (0);
}
