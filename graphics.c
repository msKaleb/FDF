/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:33:00 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/23 12:42:30 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/*
*In order to know where to put the vertex, we calculate the offset
*using the values filled by the 'mlx_get_data_addr()' function:
*bits per pixel, size of line, and the endian value, then we use the formula
*'y * size_line + x * (bits_per_pixel / 8)' to change the atributes
*of a specific vertex (or pixel).
*/
void	print_vertex(t_mlx m, t_trig t, int color)
{
	char	*ptr;
	int		offset;

	if (t.x1 < 0 || t.y1 < 0)
		return ;
	if (t.x1 > DEFAULT_X || t.y1 > DEFAULT_Y)
		return ;
	offset = (t.y1 * m.sl) + (t.x1 * (m.bpp / 8));
	ptr = m.addr + offset;
	*(unsigned int *)ptr = color;
}

/* 
*Function to convert xyz coordinates to screen xy coordinates
**TRUE_ISO: 30º angle
**ISO: 26.57º angle 
*/
void	xyztoiso(t_vertex **v)
{
	float	scr_x;
	float	scr_y;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
		{
		scr_x = (v[i][j].x - v[i][j].y) * cos(TRUE_ISO);
		scr_y = (v[i][j].x + v[i][j].y) * sin(TRUE_ISO) - v[i][j].z;
		v[i][j].scr_x = scr_x;
		v[i][j].scr_y = scr_y;
		}
		j = -1;
	}
}

/*
*Converts every hexadecimal color that is not in the format
*of 0xFFFFFF (eg 0xff -> 0x0000FF or 0xff00 -> 0x00FF00)
*/
char	*parse_color(char *str)
{
	char	*color;
	int		i;
	int		len;

	color = malloc(7);
	color[6] = '\0';
	len = ft_strlen(str);
	if (ft_isalnum(str[len - 1]) == 0)
		len--;
	i = 6;
	while (i--)
		color[i] = '0';
	i = 5;
	while (len--)
		color[i--] = ft_toupper(str[len]);
	return (color);
}

/*
*TODO:
**		Check the use of mlx_get_color_value()
*/
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

/*
*Iterate through the double pointer and draw the lines
*between two given vertices. Different conditions are
*needed to appropriately fill the grid on the boundaries.
*/
void	print_lines(t_vertex **v, t_mlx m)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
		{
			if (j == v[0]->size_x - 1)
				bresenham(v[i][j], v[i][j - 1], m);
			else
				bresenham(v[i][j], v[i][j + 1], m);
			if (i < v[0]->size_y - 1)
				bresenham(v[i][j], v[i + 1][j], m);
		}
		j = -1;
	}
}

/* void	xyztoiso(t_vertex *v)
{
	int		scr_x;
	int		scr_y;

	scr_x = (v->x - v->y) * cos(TRUE_ISO);
	scr_y = -v->z + (v->x + v->y) * sin(TRUE_ISO);
	v->x = scr_x;
	v->y = scr_y;
} */