/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:27:31 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/23 14:32:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	center_map(t_mlx *m)
{
	t_map_limits	ml;
	int				i;
	int				j;

	i = -1;
	j = -1;
	ml = get_limits(m->v);
	while (++i < m->v[0]->size_y)
	{
		while (++j < m->v[i]->size_x)
		{
			m->v[i][j].scr_x -= ml.xmin;
			m->v[i][j].scr_x += (DEFAULT_X - ml.map_width) / 2;
			m->v[i][j].scr_y -= ml.ymin;
			m->v[i][j].scr_y += (DEFAULT_Y - ml.map_height) / 2;
		}
		j = -1;
	}
}

/* 	if (dir < 0)
		{
			m->v[i][j].scr_x *= 0.9;
			m->v[i][j].scr_y *= 0.9;
			m->v[i][j].x *= 0.9;
			m->v[i][j].y *= 0.9;
			m->v[i][j].z *= 0.9;
		}
	else
		{
			m->v[i][j].scr_x /= 0.9;
			m->v[i][j].scr_y /= 0.9;
			m->v[i][j].x /= 0.9;
			m->v[i][j].y /= 0.9;
			m->v[i][j].z /= 0.9;
		} */
		
void	apply_zoom(t_vertex *v, int dir)
{
	if (dir < 0)
		{
			v->scr_x *= 0.9;
			v->scr_y *= 0.9;
			v->x *= 0.9;
			v->y *= 0.9;
			v->z *= 0.9;
		}
	else
		{
			v->scr_x /= 0.9;
			v->scr_y /= 0.9;
			v->x /= 0.9;
			v->y /= 0.9;
			v->z /= 0.9;
		}
}

void	zoom(t_mlx *m, int x, int y, int dir)
{
	int		i;
	int		j;

	(void) x;
	(void) y;
	i = -1;
	j = -1;
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	while (++i < m->v[0]->size_y)
	{
		while (++j < m->v[i]->size_x)
		{
			if (dir < 0)
				apply_zoom(&m->v[i][j], -1);
			else
				apply_zoom(&m->v[i][j], 1);
		}
		j = -1;
	}
	center_map(m);
	print_lines(m->v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

void	move_map(t_mlx *m, int x, int y)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	while (++i < m->v[0]->size_y)
	{
		while (++j < m->v[i]->size_x)
		{
			m->v[i][j].scr_x += x;
			m->v[i][j].scr_y += y;
		}
		j = -1;
	}
	print_lines(m->v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

/*
*tmp[0] = tmpx
*tmp[1] = tmpy
*/
void	rotate_map(t_vertex **v, t_mlx *m, float angle)
{
	float	angle_rad;
	float	tmp[2];
	int		i;
	int		j;

	i = -1;
	j = -1;
	angle_rad = angle * (M_PI / 180);
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
		{
			tmp[0] = v[i][j].x;
			tmp[1] = v[i][j].y;
			v[i][j].x = tmp[0] * cos(angle_rad) + tmp[1] * sin(angle_rad);
			v[i][j].y = -tmp[0] * sin(angle_rad) + tmp[1] * cos(angle_rad);
		}
		j = -1;
	}
	xyztoiso(m->v);
	center_map(m);
	print_lines(v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}
