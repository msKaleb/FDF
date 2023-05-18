/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:32:07 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/18 11:09:06 by msoria-j         ###   ########.fr       */
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

void	negtopos(t_vertex **v, t_map_limits ml)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
		{
			v[i][j].x += ft_fabs(ml.xmin);
			v[i][j].y += ft_fabs(ml.ymin);
		}
		j = -1;
	}
}

/*
For debugging purposes
*/
/* void	print_mlvalues(t_map_limits ml)
{
	printf("ml.xmin: %f - ml.xmax: %f\nml.ymin: %f - ml.ymax: %f\n", \
		ml.xmin, ml.xmax, ml.ymin, ml.ymax);
	printf("ml.map_width: %f - ml.map_height: %f\n", \
		ml.map_width, ml.map_height);
	printf("map_ar: %f - win_ar: %f\n", \
		ml.map_width / ml.map_height, DEFAULT_X / DEFAULT_Y);
} */

/*
*Return the scaling factor, acording to the aspect ratio of the map.
*/
float	scaling_factor(t_map_limits ml)
{
	if ((ml.map_width / ml.map_height) > (DEFAULT_X / DEFAULT_Y))
		return (DEFAULT_X / ml.map_width);
	else
		return (DEFAULT_Y / ml.map_height);
}

/*
*TODO:
**		Adjust the offset in X
**		Implement offset in Y
*Frame the map in the canvas.
*The offset is get by substracting the scaled width of the map
*to the width of the window divided by two (to put it in the center).
*/
void	frame_map(t_vertex **v)
{
	t_map_limits	ml;
	float			offset;
	float			sf;
	int				i;
	int				j;

	ml = get_limits(v);
	sf = scaling_factor(ml);
	offset = (DEFAULT_X - (ml.map_width * sf)) / 2;
	if (ml.xmin < 0 || ml.ymin < 0)
		negtopos(v, ml);
	i = -1;
	j = -1;
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
		{
			v[i][j].x *= sf;
			v[i][j].x += offset;
			v[i][j].y *= sf;
		}
		j = -1;
	}
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
