/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:30:22 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/03 10:05:07 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	long_slope(t_mlx m, t_trig t)
{
	(void)m;
	(void)t;
	ft_fprintf(1, "large slope\n");
	return;
}

 /* do I need v1 and v2 for color? */
void	print_line(t_mlx m, t_trig t)
{
	int	slope;

	slope = t.dy / t.dx;
	if (slope < 1)
	{
		while (t.x1 < t.x2)
		{
			mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, DEFAULT_COLOR); // change color to gradient
			if (t.d < 0)
				t.d += t.de;
			else
			{
				if (t.dy < 0)
					t.y1--;
				else
					t.y1++;
				t.d += t.dne;
			}
			t.x1++;
		}
	}
	else
		long_slope(m, t);
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
	if (t.dx == 0) // vertical
		while (t.y1 < t.y2)
		{
			ft_fprintf(1, "vertical\n");
			mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, v1.color);
			t.y1++;
		}
	else if (t.dy == 0) // horizontal
		while (t.x1 < t.x2)
		{
			ft_fprintf(1, "horizontal\n");
			mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, v1.color);
			t.x1++;
		}
	else if (t.dy == t.dx) // diagonal
		while (t.x1 < t.x2)
		{
			ft_fprintf(1, "diagonal\n");
			mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, v1.color);
			t.y1++;
			t.x1++;
		}
	else
		print_line(m, t);
}

	// ft_fprintf(1, "dx: %d - dy: %d - slope: %d\n", t.dx, t.dy, (t.dy / t.dx));