/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:16:47 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 15:06:57 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int		loop_hook(t_env *env)
{
	wolf(env);
	return (0);
}

int		exit_hook(t_env *env)
{
	free(env);
	exit(0);
	return (0);
}

int		main(void)
{
	t_env *env;

	env = make_env(800, 600);
	mlx_hook(env->win, 6, 0, wolf_mouse, env);
	mlx_hook(env->win, 2, 0, key_pressed, env);
	mlx_hook(env->win, 3, 0, key_released, env);
	mlx_hook(env->win, 17, 0, exit_hook, env);
	mlx_loop_hook(env->mlx, loop_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
