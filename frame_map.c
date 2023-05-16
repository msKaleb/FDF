/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:32:07 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/16 13:14:48 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	get_max_y(t_vertex **v)
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
			if (v[i][j].y > max)
				max = v[i][j].y;
		j = -1;
	}
	return (max);
}

int	get_min_y(t_vertex **v)
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
			if (v[i][j].y < min)
				min = v[i][j].y;
		j = -1;
	}
	return (min);
}
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
*Frame the map in 1/3 of the canvas (DEFAULT_X / 3)
*/
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
