/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:23:46 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 14:24:12 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	texture_util(int **textures, int i, int j)
{
	int xorcolor;
	int ycolor;
	int xycolor;

	xorcolor = (i * 256 / 32) ^ (j * 256 / 32);
	ycolor = j * 256 / 32;
	xycolor = j * 128 / 32 + i * 128 / 32;
	textures[0][32 * j + i] = 65536 * 254 * ((i != j && i != 32 - j) ? 1 : 0);
	textures[1][32 * j + i] = xycolor + 256 * xycolor + 65536 * xycolor;
	textures[2][32 * j + i] = 256 * xycolor + 65536 * xycolor;
	textures[3][32 * j + i] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
	textures[4][32 * j + i] = 256 * xorcolor;
	textures[5][32 * j + i] = 65536 * 192 * ((i % 16 && j % 16) ? 1 : 0);
	textures[6][32 * j + i] = 65536 * ycolor;
	textures[7][32 * j + i] = 128 + 256 * 128 + 65536 * 128;
}

int		**make_textures(void)
{
	int i;
	int j;
	int **result;

	i = 0;
	result = (int **)ft_memalloc(sizeof(int *) * 8);
	while (i < 8)
		result[i++] = (int *)ft_memalloc(sizeof(int) * 4096);
	i = 0;
	while (i < 32)
	{
		j = 0;
		while (j < 32)
		{
			texture_util(result, i, j);
			j++;
		}
		i++;
	}
	return (result);
}
