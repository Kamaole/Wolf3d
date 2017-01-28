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

int colors[5] = {0x006600, 0x660066, 0x3333FF, 0x00BFFF, 0x6600CC};

void 	dda_util(t_env *env)
{
	if (env->wolf->rayDirX < 0)
	{
		env->wolf->stepX = -1;
		env->wolf->sideDistX = (env->wolf->rayPosX - env->wolf->mapX)
			* env->wolf->deltaDistX;
	}
	else
	{
		env->wolf->stepX = 1;
		env->wolf->sideDistX = (env->wolf->mapX + 1.0 - env->wolf->rayPosX)
		* env->wolf->deltaDistX;
	}
	if (env->wolf->rayDirY < 0)
	{
		env->wolf->stepY = -1;
		env->wolf->sideDistY = (env->wolf->rayPosY - env->wolf->mapY)
			* env->wolf->deltaDistY;
	}
	else
	{
		env->wolf->stepY = 1;
		env->wolf->sideDistY = (env->wolf->mapY + 1.0 - env->wolf->rayPosY)
			* env->wolf->deltaDistY;
	}
}

void 	dda(t_env *env)
{
	dda_util(env);
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
}

double get_wall_dist(t_env *env)
{
	if (env->wolf->side == 0)
		return ((env->wolf->mapX - env->wolf->rayPosX + (1 - env->wolf->stepX) / 2) / env->wolf->rayDirX);
	else
		return ((env->wolf->mapY - env->wolf->rayPosY + (1 - env->wolf->stepY) / 2) / env->wolf->rayDirY);
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
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			int xorcolor = (i * 256 / 64)^(j * 256 / 64);
			int ycolor = j * 256 / 64;
			int xycolor = j * 128 / 64 + i * 128 / 64;
			result[0][64 * j + i] = 65536 * 254 * ((i != j && i != 64 - j) ? 1 : 0);
			result[1][64 * j + i] = xycolor + 256 * xycolor + 65536 * xycolor;
			result[2][64 * j + i] = 256 * xycolor + 65536 * xycolor;
			result[3][64 * j + i] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			result[4][64 * j + i] = 256 * xorcolor;
			result[5][64 * j + i] = 65536 * 192 * ((i % 16 && j % 16) ? 1 : 0);
			result[6][64 * j + i] = 65536 * ycolor;
			result[7][64 * j + i] = 128 + 256 * 128 + 65536 * 128;
			j++;
		}
		i++;
	}
	return (result);
}

void 	draw_vert(t_env *env)
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
	int texNum = worldMap[env->wolf->mapX][env->wolf->mapY] - 1;
	double wallX;
	if (env->wolf->side == 0)
		wallX = env->wolf->rayPosY + env->wolf->perpWallDist * env->wolf->rayDirY;
	else
		wallX = env->wolf->rayPosX + env->wolf->perpWallDist * env->wolf->rayDirX;
	wallX -= floor(wallX);
	int texX = (int)(wallX * 64.0);
	if (env->wolf->side == 0 && env->wolf->rayDirX > 0)
		texX = 64 - texX - 1;
	if (env->wolf->side == 1 && env->wolf->rayDirY < 0)
		texX = 64 - texX - 1;
	int y = env->wolf->draw_start - 1;
	while (++y < env->wolf->draw_end)
	{
		int d = y * 256 - env->height * 128 + env->wolf->line_len * 128;
		int texY = ((d * 64) / env->wolf->line_len) / 256;
		int color = env->textures[texNum][64 * texY + texX];
		if (env->wolf->side == 1)
			color = (color >> 1) & 8355711;
		pixel_to_img(env->img_data, env->wolf->x, y, color);
	}
	//floorcasting
	double floorXWall;
	double floorYWall;
	if (env->wolf->side == 0 && env->wolf->rayDirX > 0)
	{
		floorXWall = env->wolf->mapX;
		floorYWall = env->wolf->mapY + wallX;
	}
	else if (env->wolf->side == 0 && env->wolf->rayDirX < 0)
	{
		floorXWall = env->wolf->mapX + 1.0;
		floorYWall = env->wolf->mapY + wallX;
	}
	else if (env->wolf->side == 1 && env->wolf->rayDirY > 0)
	{
		floorXWall = env->wolf->mapX + wallX;
		floorYWall = env->wolf->mapY;
	}
	else
	{
		floorXWall = env->wolf->mapX + wallX;
		floorYWall = env->wolf->mapY + 1.0;
	}
	double distWall;
	double distPlayer;
	double currentDist;
	distWall = env->wolf->perpWallDist;
	distPlayer = 0.0;
	if (env->wolf->draw_end < 0)
		env->wolf->draw_end = env->height;
	y = env->wolf->draw_end;
	while (++y < env->height)
	{
		currentDist = env->height / (2.0 * y - env->height);
		double weight = (currentDist - distPlayer) / (distWall - distPlayer);
		double currentFloorX = weight * floorXWall + (1.0 - weight) * env->wolf->posX;
		double currentFloorY = weight * floorYWall + (1.0 - weight) * env->wolf->posY;

		int floorTexX;
		int floorTexY;
		floorTexX = (int)(currentFloorX * 64) % 64;
		floorTexY = (int)(currentFloorY * 64) % 64;
		int color = env->textures[4][64 * floorTexY + floorTexX] >> 1 & 8355711;
		pixel_to_img(env->img_data, env->wolf->x, env->height - y, color);
		color = env->textures[3][64 * floorTexY + floorTexX];
		pixel_to_img(env->img_data, env->wolf->x, y, color);
	}

}

void 	draw_img(t_env *env)
{
	env->wolf->time_tmp = env->wolf->time;
	env->wolf->time = clock();
	env->wolf->frame_time = (env->wolf->time - env->wolf->time_tmp) / CLOCKS_PER_SEC;
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->img_data->img, 0, 0);
	mlx_string_put(env->mlx, env->win, 0, 0, 0xFFFFFF, ft_itoa((int)(1 / env->wolf->frame_time)));
	free(env->img_data);
	env->img_data = make_img(env->mlx, env->width, env->height);
}

void 	wolf_util(t_env *env)
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
}

void 	set_speeds(t_env *env)
{
	printf("frame_time: %f\n", env->wolf->frame_time);
	env->wolf->move_speed = env->wolf->frame_time * 10.0;
	env->wolf->rot_speed = env->wolf->frame_time * 5.0;
}

void 	wolf(t_env *env)
{
	env->wolf->x = -1;
	while (++env->wolf->x < env->width)
	{
		wolf_util(env);
		dda(env);
		draw_vert(env);
	}
	draw_img(env);
	set_speeds(env);
}

void 	rot_vect(double *x, double *y, double theta)
{
	double x_tmp = *x;
	*x = *x * cos(theta) - *y * sin(theta);
	*y = x_tmp * sin(theta) + *y * cos(theta);
}

void 	move_camera(int keycode, t_env *env)
{
	if (keycode == 13)
	{
		if (!worldMap[(int)(env->wolf->posX + env->wolf->dirX * env->wolf->move_speed)][(int)(env->wolf->posY)])
		{
			env->wolf->posX += env->wolf->dirX * env->wolf->move_speed;
		}
		if (!worldMap[(int)(env->wolf->posX)][(int)(env->wolf->posY + env->wolf->dirY * env->wolf->move_speed)])
			env->wolf->posY += env->wolf->dirY * env->wolf->move_speed;
	}
	if (keycode == 1)
	{
		if (!worldMap[(int)(env->wolf->posX - env->wolf->dirX * env->wolf->move_speed)][(int)(env->wolf->posY)])
			env->wolf->posX -= env->wolf->dirX * env->wolf->move_speed;
		if (!worldMap[(int)(env->wolf->posX)][(int)(env->wolf->posY - env->wolf->dirY * env->wolf->move_speed)])
			env->wolf->posY -= env->wolf->dirY * env->wolf->move_speed;
	}
}

void 	rotate_camera(int keycode, t_env *env)
{
	if (keycode == 2 || keycode == 0)
	{
		rot_vect(&env->wolf->dirX, &env->wolf->dirY,
			((keycode == 2) ? -env->wolf->rot_speed : env->wolf->rot_speed));
		rot_vect(&env->wolf->planeX, &env->wolf->planeY,
			((keycode == 2) ? -env->wolf->rot_speed : env->wolf->rot_speed));
	}
}

int 	wolf_keys(int keycode, t_env *env)
{
	printf("keycode: %i\n", keycode);
	move_camera(keycode, env);
	rotate_camera(keycode, env);
	if (keycode == 53)
		exit(0);
	wolf(env);
	return (0);
}

int		main(void)
{
	clock_t launch = clock();
	t_env *env = make_env(1000, 1000);
	wolf(env);
	clock_t done = clock();
	double diff = (done - launch) / CLOCKS_PER_SEC;
	printf("%f\n", diff);

	mlx_hook(env->win, 2, 0, wolf_keys, env);
	mlx_loop(env->mlx);
	return (0);
}
