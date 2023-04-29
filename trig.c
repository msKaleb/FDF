/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:30:22 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/29 19:35:33 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	print_vertical_line(t_vertex v1, t_vertex v2, t_mlx m)
{
	int	y1 = v1.y;
	int	y2 = v2.y;
	
	if (v2.y < v1.y)
	{
		y1 = v2.y;
		y2 = v1.y;
	}
	while (y1 < y2)
	{
		mlx_pixel_put(m.mlx, m.win, v1.x, y1, v1.color);
		y1++;
	}
}

void	print_horizontal_line(t_vertex v1, t_vertex v2, t_mlx m)
{
	int	x1;
	int	x2;

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
		mlx_pixel_put(m.mlx, m.win, x1, v1.y, v1.color);
		x1++;
	}
}

t_trig	init_trig_var(t_vertex v1, t_vertex v2)
{
	t_trig t;
	
	t.dx = v2.x - v1.x;
	t.dy = v2.y - v1.y;
	t.d = 2 * t.dy - t.dx;
	t.de = 2 * t.dy;
	t.dne = 2 * (t.dy - t.dx);
	return (t);
}

void	bresenham(t_vertex v1, t_vertex v2, t_mlx m)
{
	t_trig	t; (void)m;

	t = init_trig_var(v1, v2);
	if (t.dx == 0)
		print_vertical_line(v1, v2, m);
	else if (t.dy / t.dx == 0)
		print_horizontal_line(v1, v2, m);
}
