/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:33:00 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/08 12:23:33 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/* find the screen xy with trig, should I use mlx_pixel_put? */
/* -try Joe Iddon solution- */
/* TRUE_ISO: 30º angle */
/* ISO: 26.57º angle */

/* void	xyztoiso(t_vertex *v, t_mlx m)
{
	// char	*ptr;
	// int		offset;
	int		scr_x;
	int		scr_y;
	(void)m;
	scr_x = (v->x - v->y) * cos(TRUE_ISO);
	scr_y = -v->z + (v->x + v->y) * sin(TRUE_ISO);
	// mlx_pixel_put(m.mlx, m.win, scr_x, scr_y, v->color);
	v->x = scr_x;
	v->y = scr_y;
	// offset = (v->y * m.sl) + (v->x * (m.bpp / 8)); // how is it calculated?
	// offset = (scr_y * m.sl + scr_x * (m.bpp / 8)); // do I need this?
	// ptr = m.addr + offset;
	// *(unsigned int*)ptr = v->color;
} */

/* Function to convert xyz coordinates to screen xy coordinates */
void	xyztoiso(t_vertex *v)
{
	int		scr_x;
	int		scr_y;

	scr_x = (v->x - v->y) * cos(TRUE_ISO);
	scr_y = -v->z + (v->x + v->y) * sin(TRUE_ISO);
	v->x = scr_x;
	v->y = scr_y;
}

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

/* TODO: adapt to Norm */
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
