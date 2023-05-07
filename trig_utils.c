/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:54:01 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/07 17:18:06 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	print_tvalues(t_trig t)
{
	ft_fprintf(1, "x1: %d - y1: %d\n", t.x1, t.y1);
	ft_fprintf(1, "x2: %d - y2: %d\n", t.x2, t.y2);
	ft_fprintf(1, "dx: %d - dy: %d\n", t.dx, t.dy);
	ft_fprintf(1, "d: %d\n", t.d);
	ft_fprintf(1, "de: %d\n", t.de);
	ft_fprintf(1, "dne: %d\n", t.dne);
	ft_fprintf(1, "m: %d\n", t.dy / t.dx);
}

t_trig	init_trig_var(t_vertex v1, t_vertex v2)
{
	t_trig	t;

	if (v2.x < v1.x)
	{
		t.x1 = v2.x;
		t.y1 = v2.y;
		t.x2 = v1.x;
		t.y2 = v1.y;
		t.scolor = v2.color;
	}
	else
	{
		t.x1 = v1.x;
		t.y1 = v1.y;
		t.x2 = v2.x;
		t.y2 = v2.y;
	}
	t.dx = (t.x2 - t.x1);
	t.dy = (t.y2 - t.y1);
	t.d = 2 * ft_abs(t.dy) - ft_abs(t.dx);
	t.de = ft_abs(2 * t.dy);
	t.dne = (2 * ft_abs(t.dy) - 2 * ft_abs(t.dx));
	t.start = t.x1;
	t.finish = t.x2;
	return (t);
}

void	vertical_line(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
	while (t.y1 <= t.y2)
	{
		ft_fprintf(1, "vertical\n");
		mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, gradient(v1, v2, t));
		t.y1++;
	}
}

void	horizontal_line(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
	while (t.x1 <= t.x2)
	{
		ft_fprintf(1, "horizontal\n");
		mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, gradient(v1, v2, t));
		t.x1++;
	}
}

void	diagonal_line(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
		(void)m;
	(void)t;
	(void)v1;
	(void)v2;
	while (t.x1 <= t.x2)
	{
		ft_fprintf(1, "diagonal\n");
		mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, 0x00ff00);
		t.y1--;
		t.x1++;
	}
}
