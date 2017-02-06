/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:19:24 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 15:00:05 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_keys	*make_keys(void)
{
	t_keys	*result;

	result = (t_keys *)ft_memalloc(sizeof(t_keys));
	result->w = 0;
	result->a = 0;
	result->s = 0;
	result->d = 0;
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
	result->textures = make_textures();
	result->keys = make_keys();
	result->map = read_map(open("map1", O_RDWR));
	return (result);
}
