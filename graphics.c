/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:33:00 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/28 10:41:09 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	get_color(char *str)
{
	int		color;
	
	color = ft_atoi_base(str + 2, "0123456789ABCDEF");
	return (color);
}

/* Functions to draw a line between two given vertices */
/* First trying to use DDA Algotithm */
/* Next using Bresenham's Line Algorithm */
/* Implement Xiaolin Wu's line algorithm in the short term */

/* Maybe use a struct for deltas and slope */
void	dda_line(t_vertex v1, t_vertex v2, t_mlx *m)
{
	float	slope;
	int	delta_x;
	int	delta_y;
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	
	// v1.x = (v1.x - v1.y) * cos(TRUE_ISO);
	// v1.y = -v1.z + (v1.x + v1.y) * sin(TRUE_ISO);
	// v2.x = (v2.x - v2.y) * cos(TRUE_ISO);
	// v2.y = -v2.z + (v2.x + v2.y) * sin(TRUE_ISO);

	// check the direction of the line
	if (v1.x > v2.x)
	{
		x1 = v2.x;
		y1 = v2.y;
		x2 = v1.x;
		y2 = v1.y;
	}
	else
	{
		x1 = v1.x;
		y1 = v1.y;
		x2 = v2.x;
		y2 = v2.y;
	}

	// calculate the slope
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	// if x2 - x1 equals 0, the line will be vertical
	if (x2 - x1 == 0)
	{
		while (y1 < y2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			y1++;
		}
		return ;
	}
	slope = delta_y / delta_x;
	
	// start creating the line
	if (slope == 1)
	{
		while (x1 < x2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			x1++;
			y1++;
		}
	}
	if (slope == 0)
	{
		while (x1 < x2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			x1++;
		}
	}
	if (slope < 1)
	{
		while (x1 < x2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			x1++;
			y1 = round(y1 + slope); // check
			// calculate the slope
			delta_x = x2 - x1;
			delta_y = y2 - y1;
			slope = delta_y / delta_x;
		}
		return ;
	}
	if (slope > 1)
	{
		while (y1 < y2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			y1++;
			x1 = round(x1 + (1 / slope)); // check
			// calculate the slope
			delta_x = x2 - x1;
			delta_y = y2 - y1;
			slope = delta_y / delta_x;
		}
		return ;
	}
}
