#ifndef WOLF_H
# define WOLF_H

#include "mlx.h"
#include "libft.h"
#include <math.h>
#include <pthread.h>

typedef struct	s_img
{
	void		*img;
	char		*data;
	int			bits;
	int			size_line;
	int			endian;
	int			height;
	int			width;
}				t_img;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef	struct	s_line
{
	t_point		*start;
	t_point		*end;
}				t_line;

typedef struct	s_wolf
{
	int			x;
	double 		posX;
	double 		posY;
	double 		dirX;
	double 		dirY;
	double 		planeX;
	double 		planeY;
	double		cameraX;
	double		rayPosX;
	double		rayPosY;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			line_len; //height of line
	int			draw_start;
	int			draw_end;
	t_line		*line;
	double 		time_tmp;
	double		time;
	double		frame_time;
	double		move_speed;
	double		rot_speed;
}				t_wolf;

typedef	struct	s_env
{
	void		*mlx;
	void 		*win;
	t_img 		*img_data;
	t_wolf		*wolf;
	int			height;
	int			width;
	int			half_height;
	int			half_width;
}				t_env;

typedef	struct	s_linevars
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err_tmp;
	int			cur_x;
	int			cur_y;
}				t_linevars;


t_img			*make_img(void *mlx, int x, int y);
t_env			*make_env(int x, int y);
t_point			*make_point(int x, int y);
t_line			*make_line(int x0, int y0, int x1, int y1);
int				line_len(int x0, int y0, int x1, int y1);
t_linevars		*get_linevars(t_line *line);
void			put_line(t_img *img_data, t_line *line, int color);
void	pixel_to_img(t_img *img_data, int x, int y, int color);
t_wolf *make_wolf(void);

#endif
