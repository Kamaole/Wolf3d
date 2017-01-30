#include "wolf.h"

void 	rot_fvect(t_fvect *vect, double theta)
{
	double x_tmp = vect->x;
	vect->x = vect->x * cos(theta) - vect->y * sin(theta);
	vect->y = x_tmp * sin(theta) + vect->y * cos(theta);
}
