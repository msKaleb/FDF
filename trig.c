/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:30:22 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/24 12:12:40 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/*
*Calculates the color gradient between two points via linear interpolation.
*We use bitshifting and bitwise operations to access to the diferent
*components of the color, being the first two bytes the red color,
*the next two the green one, and the last two corresponding to blue.
*(Transparency is not taken into account.)
*An example with the default color 0xBADA55:
*(0xBADA55 >> 16)	= 0xBA 		& 0xFF = 0xBA - Red
*(0xBADA55 >> 8)	= 0xBADA 	& 0xFF = 0xDA - Green
*(0xBADA55 >> 0)	= 0xBADA55 	& 0xFF = 0x55 - Blue
*/
int	gradient(t_trig t, float position)
{
	int	color;
	int	red;
	int	green;
	int	blue;

	red = (1 - position) * ((t.scolor >> 16) & 0xFF)
		+ ((t.fcolor >> 16) & 0xFF) * position;
	green = (1 - position) * ((t.scolor >> 8) & 0xFF)
		+ ((t.fcolor >> 8) & 0xFF) * position;
	blue = (1 - position) * (t.scolor & 0xFF)
		+ ((t.fcolor) & 0xFF) * position;
	color = ((red << 16) | (green << 8) | blue);
	return (color);
}

/*
*For predominantly horizontal lines
*/
void	bresenham_horizontal(t_mlx m, t_trig t)
{
	float	pos;
	int		sign_dy;
	int		i;

	i = 0;
	sign_dy = 1;
	if (t.y1 > t.y2)
		sign_dy = -1;
	while (i < t.dx)
	{
		t.x1++;
		if (t.d < 0)
			t.d += t.de;
		else
		{
			t.y1 += sign_dy;
			t.d += t.dne;
		}
		pos = (float)i / t.dx;
		print_vertex(m, t, gradient(t, pos));
		i++;
	}
}

/*
*For predominantly vertical lines
*/
void	bresenham_vertical(t_mlx m, t_trig t)
{
	float	pos;
	int		sign_dy;
	int		i;

	sign_dy = 1;
	if (t.y1 > t.y2)
		sign_dy = -1;
	i = 0;
	while (i < t.dy)
	{
		t.y1 += sign_dy;
		if (t.d < 0)
			t.d += t.de;
		else
		{
			t.x1++;
			t.d += t.dne;
		}
		pos = (float)i / t.dy;
		print_vertex(m, t, gradient(t, pos));
		i++;
	}
}

/*
*This function decides which of the variants has to be used:
*bresenham_horizontal() or bresenham_vertical()
*/
void	bresenham(t_vertex v1, t_vertex v2, t_mlx m)
{
	t_trig	t;

	t = init_trig_var(v1, v2);
	if (t.dx > t.dy)
		bresenham_horizontal(m, t);
	else
		bresenham_vertical(m, t);
}

t_cam	init_camera(void)
{
	t_cam	c;

	c.x = 0;
	c.y = -10;
	c.z = 10;
	c.fov = 90;
	c.pitch = -20;
	c.yaw = 20;
	return (c);
}
/*
*TODO:
**		put pitch and yaw in cam struct
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
			printf("%f - %f\n", c.yaw, c.pitch);
			printf("%f - %f\n", m->v[i][j].scr_x, m->v[i][j].scr_y);
		}
		j = -1;
	}
}

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