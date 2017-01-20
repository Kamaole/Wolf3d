#include "wolf.h"

t_wolf *make_wolf(void)
{
	t_wolf *result;

	result = (t_wolf *)ft_memalloc(sizeof(t_wolf));
	result->posX = 22;
	result->posY = 12;
	result->dirX = -1;
	result->dirY = 0;
	result->planeX = 0;
	result->planeY = .66;
	result->time = 0;
	result->time_tmp = 0;
	return (result);
}
