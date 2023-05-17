/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:32:07 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/17 10:30:50 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	init_ml(t_map_limits *ml)
{
	ml->xmax = INT_MIN;
	ml->xmin = INT_MAX;
	ml->ymax = INT_MIN;
	ml->ymin = INT_MAX;
}

t_map_limits	get_limits(t_vertex **v)
{
	t_map_limits	ml;
	int				i;
	int				j;

	i = -1;
	j = -1;
	init_ml(&ml);
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
		{
			if (v[i][j].x < ml.xmin)
				ml.xmin = v[i][j].x;
			if (v[i][j].x > ml.xmax)
				ml.xmax = v[i][j].x;
			if (v[i][j].y < ml.ymin)
				ml.ymin = v[i][j].y;
			if (v[i][j].y > ml.ymax)
				ml.ymax = v[i][j].y;
		}
		j = -1;
	}
	ml.map_width = ml.xmax - ml.xmin;
	ml.map_height = ml.ymax - ml.ymin;
	return (ml);
}

/*
*TODO:
**		min and max not needed, just the subtraction
*Frame the map in 1/3 of the canvas (DEFAULT_X / 3)
*/
void	frame_map(t_vertex **v)
{
	t_map_limits	ml;
	float			map_ar;
	float			win_ar;
	
	ml = get_limits(v);
	map_ar = ml.map_width / ml.map_height;
	win_ar = (float)(DEFAULT_X / DEFAULT_Y);
	// printf("ml.xmin: %f - ml.xmax: %f\nml.ymin: %f - ml.ymax: %f\n",\
	// 	ml.xmin, ml.xmax, ml.ymin, ml.ymax);
	// printf("ml.map_width: %f - ml.map_height: %f\n", ml.map_width, ml.map_height);
	
}

/* void	frame_map(t_vertex **v)
{
	int	i;
	int	j;
	int	dx;
	int	dy;
	int	ar;
	
	dx = get_max_x(v) - get_min_x(v);
	dy = get_max_y(v) - get_min_y(v);
	ar = dy / dx;
	int sf = DEFAULT_X / dx;
	i = -1;
	j = -1;
	ft_fprintf(1, "dx: %d - dy: %d\n", dx, dy);
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x){
			// ft_fprintf(1, "b v[i][j].x: %d\n", v[i][j].x);
			// v[i][j].x *= DEFAULT_X / 3 / dx;
			// v[i][j].x += DEFAULT_X / 3;
			// v[i][j].y *= DEFAULT_Y / 3 / dy;
			// v[i][j].y += DEFAULT_Y / 3;
			v[i][j].x *= sf;
			v[i][j].y *= sf;
			v[i][j].z *= sf;
			// ft_fprintf(1, "fp v[i][j].x: %d - v[i][j].y: %d\n", v[i][j].x, v[i][j].y);
			}
		j = -1;
	}
} */
