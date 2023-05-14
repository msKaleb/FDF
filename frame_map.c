/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:32:07 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/14 19:57:21 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	get_max_x(t_vertex **v)
{
	int	i;
	int	j;
	int	max;

	max = INT_MIN;
	i = -1;
	j = -1;
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
			if (v[i][j].x > max)
				max = v[i][j].x;
		j = -1;
	}
	return (max);
}

int	get_min_x(t_vertex **v)
{
	int	i;
	int	j;
	int	min;

	min = INT_MAX;
	i = -1;
	j = -1;
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
			if (v[i][j].x < min)
				min = v[i][j].x;
		j = -1;
	}
	return (min);
}

/*
*TODO:
**		min and max not needed, just the subtraction
*/
void	frame_map(t_vertex **v)
{
	int	i;
	int	j;
	int	max;
	int	min;
	
	max = get_max_x(v);
	min = get_min_x(v);
	i = -1;
	j = -1;
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x){
			// v[i][j].x = (DEFAULT_X / 3) + (v[i][j].x * DEFAULT_X / (max - min));
			ft_fprintf(1, "b v[i][j].x: %d\n", v[i][j].x);
			v[i][j].x *= DEFAULT_X / (max - min);
			ft_fprintf(1, "a v[i][j].x: %d\n", v[i][j].x);
			}
		j = -1;
	}
}
