/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 17:16:05 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 14:16:25 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_point		*make_point(int x, int y)
{
	t_point *result;

	result = (t_point *)ft_memalloc(sizeof(t_point));
	result->x = x;
	result->y = y;
	return (result);
}

t_line		*make_line(int x0, int y0, int x1, int y1)
{
	t_line	*result;

	result = (t_line *)ft_memalloc(sizeof(t_line));
	result->start = make_point(x0, y0);
	result->end = make_point(x1, y1);
	return (result);
}

int			line_len(int x0, int y0, int x1, int y1)
{
	int xx;
	int yy;

	xx = (x1 - x0) * (x1 - x0);
	yy = (y1 - y0) * (y1 - y0);
	return (sqrt(xx + yy));
}

t_linevars	*get_linevars(t_line *line)
{
	t_linevars *vars;

	vars = (t_linevars *)ft_memalloc(sizeof(t_linevars));
	vars->dx = abs(line->end->x - line->start->x);
	vars->dy = abs(line->end->y - line->start->y);
	vars->sx = (line->start->x < line->end->x) ? 1 : -1;
	vars->sy = (line->start->y < line->end->y) ? 1 : -1;
	vars->err = (vars->dx > vars->dy ? vars->dx : -(vars->dy)) / 2;
	vars->cur_x = line->start->x;
	vars->cur_y = line->start->y;
	return (vars);
}

void		put_line(t_img *img_data, t_line *line, int color)
{
	t_linevars *vars;

	if (line_len(line->start->x, line->start->y, line->end->x, line->end->y)
	== 0)
		return ;
	vars = get_linevars(line);
	while (!(vars->cur_x == line->end->x && vars->cur_y == line->end->y))
	{
		pixel_to_img(img_data, vars->cur_x, vars->cur_y, color);
		vars->err_tmp = vars->err;
		if (vars->err_tmp > -(vars->dx))
		{
			vars->err -= vars->dy;
			vars->cur_x += vars->sx;
		}
		if (vars->err_tmp < vars->dy)
		{
			vars->err += vars->dx;
			vars->cur_y += vars->sy;
		}
	}
	pixel_to_img(img_data, vars->cur_x, vars->cur_y, color);
}
