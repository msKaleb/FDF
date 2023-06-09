/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ops_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:27:31 by msoria-j          #+#    #+#             */
/*   Updated: 2023/06/02 08:39:57 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

/*
*To center the map, we first put each vertex to the previous smallest
*position, and then move it to its respective center of the screen.
*/
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

/*
*Function to actually apply the zoom. It is called in every iteration
*through the array/map.
*/
static void	apply_zoom(t_vertex *v, int dir)
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

/*
*For zooming in and out, either multiply or divide by 0.9, depending
*on the direction. Next re-center the map.
*/
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
			apply_zoom(&m->v[i][j], dir);
		j = -1;
	}
	center_map(m);
	print_lines(m->v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

/*
*Apply the given offset to each vertex in the map.
*/
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
*Rotate the map using rotation matrices.
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
