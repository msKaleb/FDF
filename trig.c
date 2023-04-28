/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:30:22 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/28 18:13:32 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

t_trig	init_trig_var(t_vertex v1, t_vertex v2)
{
	t_trig t;
	
	if (v1.x < v2.x)
	{
		t.dx = v2.x - v1.x;
		t.dy = v2.y - v1.y;
		t.x1 = v1.x;
		t.y1 = v1.y;
		t.x2 = v2.x;
		t.y2 = v2.y;
		t.z = v1.z;
	}
	else
	{
		t.dx = v1.x - v2.x;
		t.dy = v1.y - v2.y;
		t.x1 = v2.x;
		t.y1 = v2.y;
		t.x2 = v1.x;
		t.y2 = v1.y;
		t.z = v2.z;
	}
	ft_fprintf(1, "v1.y: %d - v2.y: %d\n", v1.y, v2.y);
	t.d = 2 * t.dy - t.dx;
	t.de = 2 * t.dy;
	t.dne = 2 * (t.dy - t.dx);
	return (t);
}

void	bresenham(t_vertex v1, t_vertex v2, t_mlx m)
{
	t_trig		 t;
	t_vertex	v;
	t = init_trig_var(v1, v2);
	// ft_fprintf(1, "t.x1: %d - t.x2: %d\n", t.x1, t.x2);
	
	while (t.x1 <= t.x2)
	{
		if (t.d <= 0)
		{
			t.d += t.de;
			t.x1 += 1;
		}
		else if (t.d > 0)
		{
			t.d += t.dne;
			t.y1 += 1;
			t.x1 += 1;
		}
	// mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, v1.color);
	v.x = t.x1;
	v.y = t.y1;
	// ft_fprintf(1, "d: %d - de: %d\n", t.d, t.de);
	// ft_fprintf(1, "v.x: %d - v.y: %d --- ", v.x, v.y);
	// ft_fprintf(1, "v1.x: %d - v1.y: %d\n", v1.x, v1.y);
	put_vertex(v, m);
	}
}
