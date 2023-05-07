/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:30:22 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/07 17:20:03 by msoria-j         ###   ########.fr       */
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
/* esta está mal */
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
void	get_deltas(t_trig *t)
{
	// t->d = t->dy < t->dx ? 2 * t->dy - t->dx : 2 * t->dx - t->dy;
	if (ft_abs(t->dy) > ft_abs(t->dx))
	{
		t->d = 2 * ft_abs(t->dx) - ft_abs(t->dy);
		t->de = 2 * ft_abs(t->dx);
		t->dne = 2 * (ft_abs(t->dx) - ft_abs(t->dy));
		t->start = t->y1;
		t->finish = t->y2;
	}
}

void	short_slope(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
	int	sign_dy;
	int	sign_dx;

	sign_dx = 1;
	if (t.dx < 0)
		sign_dx = -1;
	sign_dy = 1;
	if (t.dy < 0)
		sign_dy = -1;
	ft_fprintf(1, "short slope\n");
	get_deltas(&t);
	ft_fprintf(1, "absdy: %d - absdx: %d\n", ft_abs(t.dy), ft_abs(t.dx));
	if (ft_abs(t.dy) < ft_abs(t.dx)){
	while (t.x1 < t.x2)
	{
		// t.x1 = t.dx < 0 ? t.x1 -1: t.x1 + 1; // change
		t.x1 = t.dx < 0 ? t.x1 -1: t.x1 + 1; // change
		if (t.d < 0)
			t.d += t.de;
		else
		{
			t.y1 += sign_dy;
			t.d += t.dne;
		}
		ft_fprintf(1, "ss x1: %d - y1: %d\n", t.x1, t.y1);
		ft_fprintf(1, "ss dx: %d - dy: %d - d: %d\n", t.x2 - t.x1, t.y2 - t.y1, t.d);
		// ft_fprintf(1, "ss x2: %d - y2: %d\n", t.x2, t.y2);
		mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, gradient(v1, v2, t));
	}
	}else if (t.y1 > t.y2)/* (ft_abs(t.dy) > ft_abs(t.dx)) */{
	while (t.y1 >= t.y2)
	{
		// t.x1 = t.dx < 0 ? t.x1 -1: t.x1 + 1; // change
		t.y1--; // change
		if (t.d < 0)
			t.d += t.de;
		else
		{
			t.x1 += sign_dx;
			t.d += t.dne;
		}
		// ft_fprintf(1, "ss x2: %d - y2: %d\n", t.x2, t.y2);
		mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, 0x00ff00);
	}
	}
}

/* t.dy negative???? */
void	print_line(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
	int	slope;

	slope = t.dy / t.dx;
	if (slope < 1)
		short_slope(v1, v2, m, t);
	else if (slope >= 1)
		long_slope(v1, v2, m, t);
}

void	bresenham(t_vertex v1, t_vertex v2, t_mlx m)
{
	t_trig	t;

	t = init_trig_var(v1, v2);
	print_tvalues(t);
	if (t.dx == 0)
		vertical_line(v1, v2, m, t);
	else if (t.dy == 0)
		horizontal_line(v1, v2, m, t);
	else if ((t.dy % t.dx) == 0 && (t.dy / t.dx) == 1)
		diagonal_line(v1, v2, m, t);
	else
		print_line(v1, v2, m, t);
}
