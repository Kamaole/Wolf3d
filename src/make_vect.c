#include "wolf.h"

t_vect 	*make_vect(int x, int y)
{
	t_vect *result;

	result = (t_vect *)ft_memalloc(sizeof(t_vect));
	result->x = x;
	result->y = y;
	return (result);
}

t_fvect 	*make_fvect(double x, double y)
{
	t_fvect *result;

	result = (t_fvect *)ft_memalloc(sizeof(t_fvect));
	result->x = x;
	result->y = y;
	return (result);
}
