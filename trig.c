/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:30:22 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/08 12:10:28 by msoria-j         ###   ########.fr       */
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

void	bresenham_horizontal(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
	int	sign_dy;

	sign_dy = 1;
	if (t.y1 > t.y2)
		sign_dy = -1;
	while (t.dx--)
	{
		t.x1++;
		if (t.d < 0)
			t.d += t.de;
		else
		{
			t.y1 += sign_dy;
			t.d += t.dne;
		}
		mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, gradient(v1, v2, t));
	}
}

void	bresenham_vertical(t_vertex v1, t_vertex v2, t_mlx m, t_trig t)
{
	int	sign_dy;

	sign_dy = 1;
	if (t.y1 > t.y2)
		sign_dy = -1;
	while ((t.dy)--)
	{
		t.y1 += sign_dy;
		if (t.d < 0)
			t.d += t.de;
		else
		{
			t.x1++;
			t.d += t.dne;
		}
		mlx_pixel_put(m.mlx, m.win, t.x1, t.y1, gradient(v1, v2, t));
	}
}

void	bresenham(t_vertex v1, t_vertex v2, t_mlx m)
{
	t_trig	t;

	t = init_trig_var(v1, v2);
	if (t.dx > t.dy)
		bresenham_horizontal(v1, v2, m, t);
	else
		bresenham_vertical(v1, v2, m, t);
}
