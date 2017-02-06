/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:13:00 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 14:13:15 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_img(t_env *env)
{
	env->wolf->time_tmp = env->wolf->time;
	env->wolf->time = clock();
	env->wolf->frame_time = (env->wolf->time - env->wolf->time_tmp)
		/ CLOCKS_PER_SEC;
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->img_data->img, 0, 0);
	mlx_string_put(env->mlx, env->win, 0, 0, 0xFFFFFF,
		ft_itoa((int)(1 / env->wolf->frame_time)));
	free(env->img_data);
	env->img_data = make_img(env->mlx, env->width, env->height);
}
