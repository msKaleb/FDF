/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:30:22 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/02 13:40:24 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/* void	print_vertex(t_vertex v, t_mlx m)
{
	int		scr_x;
	int		scr_y;
	
	scr_x = (v.x - v.y) * cos(TRUE_ISO);
	scr_y = -v.z + (v.x + v.y) * sin(TRUE_ISO);
	// ft_fprintf(1, "x: %d y: %d\n", v.x, v.y);
	mlx_pixel_put(m.mlx, m.win, scr_x, scr_y, v.color);
} */
/* no funciona, primero posicionar vértices en 3d
   y después tirar las lineas */
void	print_vertical_line(t_vertex v1, t_vertex v2, t_mlx m) // change, add t_trig t
{
	int	y1 = v1.y;
	int	y2 = v2.y;
	t_vertex	v;
	
	if (v2.y < v1.y)
	{
		y1 = v2.y;
		y2 = v1.y;
	}
	while (y1 < y2)
	{
		v.x = v1.x;
		v.y = y1;
		v.z = v1.z;
		// print_vertex(v, m);
		// ft_fprintf(1, "vert x: %d\n", v.x);
		// mlx_pixel_put(m.mlx, m.win, (v.x - v.y) * cos(TRUE_ISO), -v.z + (v.x + v.y) * sin(TRUE_ISO), v1.color);
		mlx_pixel_put(m.mlx, m.win, v.x, v.y, v1.color);
		y1++;
	}
}

void	print_horizontal_line(t_vertex v1, t_vertex v2, t_mlx m) // change, add t_trig t
{
	int	x1;
	int	x2;
	t_vertex	v;
	
	if (v2.x < v1.x)
	{
		x1 = v2.x;
		x2 = v1.x;
	}
	else
	{
		x1 = v1.x;
		x2 = v2.x;
	}
	while (x1 < x2)
	{
		v.x = x1;
		v.y = v1.y;
		v.z = v1.z;
		// mlx_pixel_put(m.mlx, m.win, (v.x - v.y) * cos(TRUE_ISO), -v.z + (v.x + v.y) * sin(TRUE_ISO), v1.color);
		mlx_pixel_put(m.mlx, m.win, v.x, v.y, v1.color);
		x1++;
	}
	// ft_fprintf(1, "---------------------\n");
}

void	print_diagonal_line(t_vertex v1, t_vertex v2, t_mlx m) // change, add t_trig t
{
	int	x1;
	int	x2;
	int	y;
	
	if (v2.x < v1.x)
	{
		y = v2.y;
		x1 = v2.x;
		x2 = v1.x;
	}
	else
	{
		y = v1.y;
		x1 = v1.x;
		x2 = v2.x;
	}
	while (x1 < x2)
	{
		// mlx_pixel_put(m.mlx, m.win, (v.x - v.y) * cos(TRUE_ISO), -v.z + (v.x + v.y) * sin(TRUE_ISO), v1.color);
		mlx_pixel_put(m.mlx, m.win, x1, y, v1.color);
		y++;
		x1++;
	}
}

void	print_line(t_mlx m, t_trig t)
{
	float	slope;
(void)m;
	slope = t.dy / t.dx;
	if (slope < 1)
	{
		while (t.x1 < t.x2)
		{
			
			mlx_pixel_put(m.mlx, m.win, x1, y, DEFAULT_COLOR); // change color to gradient
			t.d = 2 * t.dy - t.dx;
			t.x1++;
		}
		return;
	}
}

t_trig	init_trig_var(t_vertex v1, t_vertex v2)
{
	t_trig t;
	
	if (v2.x < v1.x)
	{
		t.x1 = v2.x;
		t.y1 = v2.y;
		t.x2 = v1.x;
		t.y2 = v1.y;
	}
	else
	{
		t.x1 = v1.x;
		t.y1 = v1.y;
		t.x2 = v2.x;
		t.y2 = v2.y;
	}
	t.dx = t.x2 - t.x1;
	t.dy = t.y2 - t.y1;
	t.d = 2 * t.dy - t.dx;
	t.de = 2 * t.dy;
	t.dne = 2 * (t.dy - t.dx);
	return (t);
}

void	bresenham(t_vertex v1, t_vertex v2, t_mlx m)
{
	t_trig	t;

	t = init_trig_var(v1, v2);
	// ft_fprintf(1, "t.dy: %d - t.dx: %d\n", t.dy, t.dx);
	if (t.dx == 0)
		print_vertical_line(v1, v2, m);
	else if (t.dy == 0)
		print_horizontal_line(v1, v2, m);
	else if (t.dy == t.dx)
		print_diagonal_line(v1, v2, m);
	else
		print_line(m, t);
	ft_fprintf(1, "dx: %d - dy: %d - slope: %d\n", t.dx, t.dy, (t.dy / t.dx));
	return;
}
