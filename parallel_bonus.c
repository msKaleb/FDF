/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:46:59 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/30 13:14:01 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

/* static void	get_scr_coordinates(t_mlx *m, int view)
{
	float	angle_rad;
	float	tmp[2];

	angle_rad = 90 * (M_PI / 180);
	if (view == XK_UP)
	{
		m->v[i][j].scr_x = m->v[i][j].x;
		m->v[i][j].scr_y = m->v[i][j].y;
	}
	else if (view == XK_LEFT)
	{
		tmp[0] = m->v[i][j].x;
		tmp[1] = m->v[i][j].y;
		m->v[i][j].x = tmp[0] * cos(angle_rad) + tmp[1] * sin(angle_rad);
		m->v[i][j].y = -tmp[0] * sin(angle_rad) + tmp[1] * cos(angle_rad);
	}
	else if (view == XK_DOWN)
	{
		m->v[i][j].scr_x = m->v[i][j].x;
		m->v[i][j].scr_y = -m->v[i][j].z;
	}
} */

void	parallel_right(t_mlx *m)
{
	float	angle_rad;
	float	tmp[2];
	int		i;
	int		j;

	i = -1;
	j = -1;
	angle_rad = 90 * (M_PI / 180);
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	while (++i < m->v[0]->size_y)
	{
		while (++j < m->v[i]->size_x)
		{
			tmp[0] = m->v[i][j].x;
			tmp[1] = m->v[i][j].y;
			m->v[i][j].scr_x = tmp[0] * cos(angle_rad)
				+ tmp[1] * sin(angle_rad);
			m->v[i][j].scr_y = -m->v[i][j].z;
		}
		j = -1;
	}
	center_map(m);
	print_lines(m->v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

void	parallel_left(t_mlx *m)
{
	float	angle_rad;
	float	tmp[2];
	int		i;
	int		j;

	i = -1;
	j = -1;
	angle_rad = -90 * (M_PI / 180);
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	while (++i < m->v[0]->size_y)
	{
		while (++j < m->v[i]->size_x)
		{
			tmp[0] = m->v[i][j].x;
			tmp[1] = m->v[i][j].y;
			m->v[i][j].scr_x = tmp[0] * cos(angle_rad)
				+ tmp[1] * sin(angle_rad);
			m->v[i][j].scr_y = -m->v[i][j].z;
		}
		j = -1;
	}
	center_map(m);
	print_lines(m->v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

void	parallel(int view, t_mlx *m)
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
			m->v[i][j].scr_x = m->v[i][j].x;
			if (view == XK_UP)
				m->v[i][j].scr_y = m->v[i][j].y;
			else if (view == XK_DOWN)
				m->v[i][j].scr_y = -m->v[i][j].z;
		}
		j = -1;
	}
	center_map(m);
	print_lines(m->v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}
