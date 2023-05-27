/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:44:21 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/27 13:51:56 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

t_cam	init_camera(void)
{
	t_cam	c;

	c.x = 0;
	c.y = 15;
	c.z = 20;
	c.fov = 90;
	c.pitch = 0;
	c.yaw = 0;
	return (c);
}

/*
*Function to implement Joe Iddon's method to represent
*vertices in screen (provisional) - (BROKEN)
*/
void	xyztoperspective(t_mlx *m)
{
	t_cam	c;
	int		i;
	int		j;

	c = init_camera();
	i = -1;
	j = -1;
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	while (++i < m->v[0]->size_y)
	{
		while (++j < m->v[i]->size_x)
		{
			c.yaw = (atan2(m->v[i][j].x - c.x, m->v[i][j].y - c.y)
					* (180 / M_PI));
			c.pitch = (atan2(m->v[i][j].z - c.z, m->v[i][j].y - c.y)
					* (180 / M_PI));
			m->v[i][j].scr_x = DEFAULT_X / 2
				+ (c.yaw * (DEFAULT_X / c.fov));
			m->v[i][j].scr_y = DEFAULT_Y / 2
				- (c.pitch * (DEFAULT_X / c.fov));
		}
		j = -1;
	}
	center_map(m);
	print_lines(m->v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

/* void	xyztoperspective(t_mlx *m)
{
	t_cam	c;
	int		i;
	int		j;
	int		nx, ny;
	
	c = init_camera();
	i = -1;
	j = -1;
	mlx_destroy_image(m->mlx, m->img);
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	while (++i < m->v[0]->size_y)
	{
		while (++j < m->v[i]->size_x)
		{
			m->v[i][j].scr_x = c.x / -c.y;
			m->v[i][j].scr_y = c.z / -c.y;
			nx = (m->v[i][j].scr_x + DEFAULT_X / 2) / DEFAULT_X;
			ny = (m->v[i][j].scr_y + DEFAULT_Y / 2) / DEFAULT_Y;
			m->v[i][j].scr_x = floorf(nx * DEFAULT_X);
			m->v[i][j].scr_y = floorf((1 - ny) * DEFAULT_Y);
		}
		j = -1;
	}
	center_map(m);
	print_lines(m->v, *m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
} */

/* void	xyztoperspective(t_vertex **v)
{
	int		pitch;
	int		yaw;
	int		scr_x;
	int		scr_y;
	int		i;
	int		j;
	t_cam	cam;

	i = -1;
	j = -1;
	cam.x = 0;
	cam.y = 10;
	cam.z = 0;
	cam.fov = 50;
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
		{
		yaw = atan2(v[i][j].x - cam.x, v[i][j].y - cam.y) * (180 / M_PI);
		pitch = atan2(v[i][j].z - cam.z, v[i][j].y - cam.y) * (180 / M_PI);
		scr_x = DEFAULT_X / 2 + (yaw * (DEFAULT_X / cam.fov));
		scr_y = DEFAULT_Y / 2 - (pitch * (DEFAULT_X / cam.fov));
		ft_fprintf(1, "v[i][j].x: %d, v[i][j].y: %d\n", v[i][j].x, v[i][j].y);
		v[i][j].x = scr_x;
		v[i][j].y = scr_y;
		ft_fprintf(1, "x: %d, y: %d\n", scr_x, scr_y);
		ft_fprintf(1, "pitch: %d, yaw: %d\n", pitch, yaw);
		// yaw = atan2(v[i][j].x - cam.x, v[i][j].y - cam.y) * (180 / M_PI);
		// pitch = atan2(v[i][j].z - cam.z, v[i][j].y - cam.y) * (180 / M_PI);
		// scr_x = DEFAULT_X / 2 + (yaw * (DEFAULT_X / cam.fov));
		// scr_y = DEFAULT_Y / 2 - (pitch * (DEFAULT_X / cam.fov));
		// ft_fprintf(1, "v->x: %d, v->y: %d\n", v[i][j].x, v[i][j].y);
		// v[i][j].x = scr_x;
		// v[i][j].y = scr_y;
		// ft_fprintf(1, "pitch: %d, yaw: %d\n", pitch, yaw);
		// ft_fprintf(1, "x: %d, y: %d\n", scr_x, scr_y);
		}
		j = -1;
	}
}
 */