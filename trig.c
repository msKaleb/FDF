/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:30:22 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/10 09:34:41 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/* Calculates the color gradient between two points via linear interpolation.*/
/* We use bitshifting and bitwise operations to access to the diferent */
/* components of the color, being the first two bytes the red color, */
/* the next two the green one, and the last two corresponding to blue. */
/* (Transparency is not taken into account.) */
/* An example with the default color 0xBADA55: */
/* (0xBADA55 >> 16)	= 0xBA 		& 0xFF = 0xBA - Red */
/* (0xBADA55 >> 8)	= 0xBADA 	& 0xFF = 0xDA - Green */
/* (0xBADA55 >> 0)	= 0xBADA55 	& 0xFF = 0x55 - Blue */
int	gradient(t_trig t, float position)
{
	int	color;
	int	red;
	int	green;
	int	blue;

	red = (1 - position) * ((t.scolor >> 16) & 0xFF)
		+ ((t.fcolor >> 16) & 0xFF) * position;
	green = (1 - position) * ((t.scolor >> 8) & 0xFF)
		+ ((t.fcolor >> 8) & 0xFF) * position;
	blue = (1 - position) * (t.scolor & 0xFF)
		+ ((t.fcolor) & 0xFF) * position;
	color = ((red << 16) | (green << 8) | blue);
	return (color);
}

void	bresenham_horizontal(t_mlx m, t_trig t)
{
	float	pos;
	int		sign_dy;
	int		i;

	i = 0;
	sign_dy = 1;
	if (t.y1 > t.y2)
		sign_dy = -1;
	while (i < t.dx)
	{
		t.x1++;
		if (t.d < 0)
			t.d += t.de;
		else
		{
			t.y1 += sign_dy;
			t.d += t.dne;
		}
		pos = (float)i / t.dx;
		print_vertex(m, t, gradient(t, pos));
		i++;
	}
}

void	bresenham_vertical(t_mlx m, t_trig t)
{
	float	pos;
	int		sign_dy;
	int		i;

	sign_dy = 1;
	if (t.y1 > t.y2)
		sign_dy = -1;
	i = 0;
	while (i < t.dy)
	{
		t.y1 += sign_dy;
		if (t.d < 0)
			t.d += t.de;
		else
		{
			t.x1++;
			t.d += t.dne;
		}
		pos = (float)i / t.dy;
		print_vertex(m, t, gradient(t, pos));
		i++;
	}
}

void	bresenham(t_vertex v1, t_vertex v2, t_mlx m)
{
	t_trig	t;

	t = init_trig_var(v1, v2);
	if (t.dx > t.dy)
		bresenham_horizontal(m, t);
	else
		bresenham_vertical(m, t);
}
