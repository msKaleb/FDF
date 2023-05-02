/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:33:00 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/02 12:15:29 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/* find the screen xy with trig, should I use mlx_pixel_put? */
/* -try Joe Iddon solution- */
/* TRUE_ISO: 30º angle */
/* ISO: 26.57º angle */
/* change or create a new array with the new values */
void	put_vertex(t_vertex *v, t_mlx m)
{
	// char	*ptr;
	// int		offset;
	int		scr_x;
	int		scr_y;
	
	scr_x = (v->x - v->y) * cos(TRUE_ISO);
	scr_y = -v->z + (v->x + v->y) * sin(TRUE_ISO);
	// mlx_pixel_put(m.mlx, m.win, scr_x, scr_y, v->color);
	v->x = scr_x;
	v->y = scr_y;
	mlx_pixel_put(m.mlx, m.win, v->x, v->y, v->color);
	// offset = (v->y * m.sl) + (v->x * (m.bpp / 8)); // how is it calculated?
	// offset = (scr_y * m.sl + scr_x * (m.bpp / 8)); // do I need this?
	// ptr = m.addr + offset;
	// *(unsigned int*)ptr = v->color;
}

char	*parse_color(char *str)
{
	char	*color;
	int		i;
	int		len;

	color = malloc(7);
	color[6] = '\0';
	len = ft_strlen(str);
	// ft_fprintf(1, "str: %s\t", str);
	if (ft_isalnum(str[len - 1]) == 0)
		len--;
	// ft_fprintf(1, "len: %d\t", len);
	i = 6;
	while (i--)
		color[i] = '0';
	i = 5;
	while (len--)
		color[i--] = ft_toupper(str[len]);
	// ft_fprintf(1, "color: %s\n", color);
	return (color);
}

int	get_color(char *str)
{
	int		color;
	int		len;
	char	*ccode;

	len = ft_strlen(str);
	if (ft_strnstr(str, ",0x", len) || ft_strnstr(str, ",0X", len))
	{
		ccode = parse_color(ft_strchr(str, ',') + 3);
		color = ft_atoi_base(ccode, "0123456789ABCDEF");
		free(ccode);
	}
	else
		color = DEFAULT_COLOR;
	return (color);
}

/* Functions to draw a line between two given vertices */
/* First trying to use DDA Algotithm */
/* Next using Bresenham's Line Algorithm */
/* Implement Xiaolin Wu's line algorithm in the short term */

/* Maybe use a struct for deltas and slope */
void	dda_line(t_vertex v1, t_vertex v2, t_mlx *m)
{
	float	slope;
	int	delta_x;
	int	delta_y;
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	
	// v1.x = (v1.x - v1.y) * cos(TRUE_ISO);
	// v1.y = -v1.z + (v1.x + v1.y) * sin(TRUE_ISO);
	// v2.x = (v2.x - v2.y) * cos(TRUE_ISO);
	// v2.y = -v2.z + (v2.x + v2.y) * sin(TRUE_ISO);

	// check the direction of the line
	if (v1.x > v2.x)
	{
		x1 = v2.x;
		y1 = v2.y;
		x2 = v1.x;
		y2 = v1.y;
	}
	else
	{
		x1 = v1.x;
		y1 = v1.y;
		x2 = v2.x;
		y2 = v2.y;
	}

	// calculate the slope
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	// if x2 - x1 equals 0, the line will be vertical
	if (x2 - x1 == 0)
	{
		while (y1 < y2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			y1++;
		}
		return ;
	}
	slope = delta_y / delta_x;
	
	// start creating the line
	if (slope == 1)
	{
		while (x1 < x2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			x1++;
			y1++;
		}
	}
	if (slope == 0)
	{
		while (x1 < x2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			x1++;
		}
	}
	if (slope < 1)
	{
		while (x1 < x2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			x1++;
			y1 = round(y1 + slope); // check
			// calculate the slope
			delta_x = x2 - x1;
			delta_y = y2 - y1;
			slope = delta_y / delta_x;
		}
		return ;
	}
	if (slope > 1)
	{
		while (y1 < y2)
		{
			mlx_pixel_put(m->mlx, m->win, x1, y1, v1.color); // change color to gradient
			y1++;
			x1 = round(x1 + (1 / slope)); // check
			// calculate the slope
			delta_x = x2 - x1;
			delta_y = y2 - y1;
			slope = delta_y / delta_x;
		}
		return ;
	}
}
