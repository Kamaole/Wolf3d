/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_and_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:21:16 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 14:22:09 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_pressed(int keycode, t_env *env)
{
	if (keycode == 13 && !env->keys->w)
		env->keys->w = 1;
	if (keycode == 0 && !env->keys->a)
		env->keys->a = 1;
	if (keycode == 1 && !env->keys->s)
		env->keys->s = 1;
	if (keycode == 2 && !env->keys->d)
		env->keys->d = 1;
	if (keycode == 53)
		exit(0);
	wolf(env);
	return (keycode);
}

int		key_released(int keycode, t_env *env)
{
	if (keycode == 13 && env->keys->w)
		env->keys->w = 0;
	if (keycode == 0 && env->keys->a)
		env->keys->a = 0;
	if (keycode == 1 && env->keys->s)
		env->keys->s = 0;
	if (keycode == 2 && env->keys->d)
		env->keys->d = 0;
	wolf(env);
	return (keycode);
}

int		wolf_mouse(int x, int y, t_env *env)
{
	rot_dvect(env->wolf->dir,
		((x > env->last_x) ? -env->wolf->rot_speed : env->wolf->rot_speed));
	rot_dvect(env->wolf->plane,
		((x > env->last_x) ? -env->wolf->rot_speed : env->wolf->rot_speed));
	env->last_x = x;
	y = 0;
	wolf(env);
	return (0);
}
