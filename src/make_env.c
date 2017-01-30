#include "wolf.h"

t_img	*make_img(void *mlx, int x, int y)
{
	t_img *result;

	result = (t_img *)ft_memalloc(sizeof(t_img));
	result->img = mlx_new_image(mlx, x, y);
	result->data = mlx_get_data_addr(result->img, &result->bits,
		&result->size_line, &result->endian);
	result->width = x;
	result->height = y;
	return (result);
}

t_env	*make_env(int x, int y)
{
	t_env *result;

	result = (t_env *)ft_memalloc(sizeof(t_env));
	result->mlx = mlx_init();
	result->win = mlx_new_window(result->mlx, x, y, "Wolf3d");
	result->img_data = make_img(result->mlx, x, y);
	result->width = x;
	result->height = y;
	result->half_width = x / 2;
	result->half_height = y / 2;
	result->wolf = make_wolf();
	result->last_x = 0;
	result->last_y = 0;
	result->textures = make_textures();
	return (result);
}
