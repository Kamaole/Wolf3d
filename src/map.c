/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:07:36 by rmatos            #+#    #+#             */
/*   Updated: 2017/02/06 15:08:30 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		**read_map(int fd)
{
	int		i;
	int		j;
	int		**result;
	char	*line;
	char	**split;

	i = 0;
	result = (int **)ft_memalloc(sizeof(int *) * 24);
	while (get_next_line(fd, &line))
	{
		j = -1;
		split = ft_strsplit(line, ' ');
		result[i] = (int *)ft_memalloc(sizeof(int) * 24);
		while (split[++j])
			result[i][j] = ft_atoi(split[j]);
		i++;
	}
	return (result);
}
