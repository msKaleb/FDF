/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:33:00 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/12 12:51:06 by msoria-j         ###   ########.fr       */
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

	offset = (t.y1 * m.sl) + (t.x1 * (m.bpp / 8));
	ptr = m.addr + offset;
	*(unsigned int*)ptr = color;
}

/* 
*Function to convert xyz coordinates to screen xy coordinates
**TRUE_ISO: 30º angle
**ISO: 26.57º angle 
*/
void	xyztoiso(t_vertex *v)
{
	int		scr_x;
	int		scr_y;

	scr_x = (v->x - v->y) * cos(TRUE_ISO);
	scr_y = -v->z + (v->x + v->y) * sin(TRUE_ISO);
	v->x = scr_x;
	v->y = scr_y;
}

/*
Converts every hexadecimal color that is not in the format
of 0xFFFFFF (eg 0xff -> 0x0000FF or 0xff00 -> 0x00FF00)
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
*TODO: 
**		Adapt to Norm 
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
			xyztoiso(&v[i][j]);
			// xyztoperspective(&v[i][j]);
		j = -1;
	}
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
