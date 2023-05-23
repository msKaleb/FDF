/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:27:31 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/23 11:12:39 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	zoom(t_mlx *m, int x, int y, int dir)
{
	int		i;
	int		j;
	(void)x;
	(void)y;
	(void)dir;
	i = -1;
	j = -1;
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	while (++i < m->v[0]->size_y)
	{
		while (++j < m->v[i]->size_x)
		{
			// printf("before x: %f - y: %f\n", m->v[i][j].scr_x, m->v[i][j].scr_y);
			if (dir < 0)
			{
				m->v[i][j].scr_x *= 0.9;
				m->v[i][j].scr_y *= 0.9;
			}
			else
			{
				m->v[i][j].scr_x /= 0.9;
				m->v[i][j].scr_y /= 0.9;
			}
			// printf("after x: %f - y: %f\n", m->v[i][j].scr_x, m->v[i][j].scr_y);
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

void	rotate_map(t_vertex **v, t_mlx *m, float angle)
{
	float	angle_rad;
	float	tmpx;
	float	tmpy;
	int		i;
	int		j;

	printf("v[0]->size_y: %d\n", v[0]->size_y);
	i = -1;
	j = -1;
	angle_rad = angle * (M_PI / 180);
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
		{
/* 			printf("v[%d][%d].x: %f - v[%d][%d].y: %f\n",\
				i, j, v[i][j].x, i, j, v[i][j].y); */
			tmpx = v[i][j].x;
			tmpy = v[i][j].y;
			printf("----------------------------\n");
			v[i][j].x = tmpx * cos(angle_rad) + tmpy * sin(angle_rad);
			v[i][j].y = -tmpx * sin(angle_rad) + tmpy * cos(angle_rad);
/* 			printf("v[%d][%d].x: %f - v[%d][%d].y: %f\n",\
				i, j, v[i][j].x, i, j, v[i][j].y); */
		}
		j = -1;
	}
	// frame_map(m->v);
	print_lines(v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}
