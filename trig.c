/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:30:22 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/05 13:15:44 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"


int	gradient(t_vertex v1, t_vertex v2, t_trig t)
{
	if (v1.x == t.x1)
		return (v1.color);
	else
		return (v2.color);
}

void	long_slope(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
	int	tmp;

	(void)m;
	(void)t;
	(void)v1;
	(void)v2;
	ft_fprintf(1, "long slope\n");

	v2.color = 0xff;
	tmp = t.x1;
	t.x1 = t.y1;
	t.y1 = tmp;
	tmp = t.x2;
	t.x2 = t.y2;
	t.y2 = tmp;
	t.dx = t.x2 - t.x1;
	t.dy = (t.y2 - t.y1);
	t.d = 2 * t.dy - t.dx;
	t.de = 2 * t.dy;
	t.dne = 2 * (t.dy - t.dx);
	// print_line(v1, v2, m, t);
}

void	short_slope(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
	ft_fprintf(1, "short slope\n");
	while (t.x1 < t.x2)
	{
		if (t.d <= 0)
		{
			if (t.dy < 0)
			{
				t.x1++;
				t.y1--;
			}
			t.d += t.de;
		}
		else
		{
			if (t.dy <= 0)
				t.y1--;
			else
				t.y1++;
			t.d += t.dne;
		}
		t.x1++;
		mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, gradient(v1, v2, t));
	}
}

/* t.dy negative???? */
void	print_line(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
	int	slope;

	print_tvalues(t);
	slope = t.dy / t.dx;
	if (slope < 0)
	{
		ft_fprintf(1, "m: %d\n", slope);
		while (t.x1 <= t.x2)
		{
			while (slope < 0){
				mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, 0xff0000);
				t.y1--;
				slope++;
				}
			t.x1++;
			slope = t.dy / t.dx;
		}
	}
	else if (slope >= 0 && slope < 1)
		short_slope(v1, v2, m, t);
	else if (slope > 1)
		long_slope(v1, v2, m, t);
}

void	bresenham(t_vertex v1, t_vertex v2, t_mlx m)
{
	t_trig	t;

	t = init_trig_var(v1, v2);
	if (t.dx == 0)
		vertical_line(v1, v2, m, t);
	else if (t.dy == 0)
		horizontal_line(v1, v2, m, t);
	else if ((t.dy / t.dx) == 1)
		diagonal_line(v1, v2, m, t);
	else
		print_line(v1, v2, m, t);
}
