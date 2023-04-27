/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/27 11:44:31 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mlx_linux/mlx.h" // For Linux
// #include"mlx/mlx.h"
#include"ft_fdf.h"
#include"LibFT/libft.h"
#include<fcntl.h>

// TODO:
// Gradient color from a to b function

int	get_color(char *str)
{
	int		color;
	
	color = ft_atoi_base(str + 2, "0123456789ABCDEF");
	return (color);
}

/* Maybe change the arguments of the function */
t_vertex	*get_coords(char **line, int y)
{
	t_vertex	*v;
	int			i;
	int			xlen;
	
	i = 0;
	while (line[i])
		i++;
	xlen = i;
	v = malloc(sizeof(t_vertex) * (xlen + 1));
	i = 0;
	if (!v)
		perror("");
	while (line[i])
	{
		// TODO: Find out a nice offset for x and y
		v[i].x = (DEFAULT_X / 3) + i * ((DEFAULT_X / 3) / xlen);
		v[i].y = y * ((DEFAULT_Y / 3) / 500);	// TODO: change 10 for number of lines in the map
		v[i].z = ft_atoi(line[i]); // TODO: Find a valid multiplier (depending on the max z value)
		if (ft_strchr(line[i], ','))
			v[i].color = get_color(ft_strchr(line[i], ',') + 1);
		else
			v[i].color = DEFAULT_COLOR;
		v[i].size_x = xlen;
		i++;
	}
	return (v);
}

void	dblfree(void **var)
{
	int	i;

	i = -1;
	while (var[++i])
		free(var[i]);
	free(var);
}

int	close_mlx(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->img);
	mlx_destroy_window(m->mlx, m->win);		
	mlx_destroy_display(m->mlx);
	free(m->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int key_code, t_mlx *m)
{
	// ft_fprintf(1, "%s\n", change_base(key_code, 'x'));
	if (key_code == XK_Escape)
		close_mlx(m);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *m)
{
	(void)m;
	ft_fprintf(1, "%d - %d - %d\n", button, x, y);
	return (0);
}

/* Function to draw a line between two given vertices */
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

/* find the screen xy with trig, should I use mlx_pixel_put? */
/* -try Joe Iddon solution- */
/* TRUE_ISO: 30º angle */
/* ISO: 26.57º angle */
void	put_vertex(t_vertex v, t_mlx m)
{
	char	*ptr;
	int		offset;
	int		scr_x;
	int		scr_y;
	
	scr_x = (v.x - v.y) * cos(TRUE_ISO);
	scr_y = -v.z + (v.x + v.y) * sin(TRUE_ISO);
	// mlx_pixel_put(m.mlx, m.win, scr_x, scr_y, v.color);
	
	// offset = (v.y * m.sl) + (v.x * (m.bpp / 8)); // how is it calculated?
	offset = (scr_y * m.sl + scr_x * (m.bpp / 8)); // do I need this?
	ptr = m.addr + offset;
	// for making each vertex of 4 pixels...
	*(unsigned int*)ptr = v.color;
	// *(unsigned int*)(ptr + 1) = v.color;
	// *(unsigned int*)(ptr + m.sl) = v.color;
	// *(unsigned int*)(ptr + m.sl + 1) = v.color;
}

void	init_mlx(t_mlx *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, DEFAULT_X, DEFAULT_Y, "Test");
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->endian);
}
int	count_rows(char *map)
{
	char	*line;
	int		rows;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		perror("Error"); // exit on error, make a function	
	rows = 0;
	while((line = get_next_line(fd)) != NULL)
		rows++;
	close(fd);
	return (rows);
}

t_vertex	**read_map(int fd, int rows)
{
	t_vertex	**v;
	char		**linexyz;
	char		*line;
	int			i;
	
	i = 0;
	v = malloc(sizeof(t_vertex *) * rows);
	while((line = get_next_line(fd)) != NULL) // TODO: make a function to read the map
	{
		linexyz = ft_split(line, ' ');
		v[i] = get_coords(linexyz, i);
		/* while (linexyz[j]) // TODO: make a linked list, and go down the list to add rows
		{
			put_vertex(v[j], m);
			// dda_line(v[x], v[x + 1], &m);
			j++;
		} */
		i++;
		// free(v);
		free(line);
		dblfree((void **)linexyz);
	}
	return (v);
}

int	main(void)
{
	t_vertex	**v;
	t_mlx		m;
	int			fd;
	// int 		x = -1;
	// int 		y = 0;
	
	// char	*test_file = "maps/42.fdf";
	char	*test_file = "maps/elem-col.fdf";
	// char	*test_file = "maps/julia.fdf";
	int	rows = count_rows(test_file);
	fd = open(test_file, O_RDONLY);
	if (fd == -1)
		perror("Error"); // exit on error, make a function
	init_mlx(&m);
	v = read_map(fd, rows);
	// print digits for testing
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < v[i]->size_x; j++)
			ft_fprintf(1, "%d ", v[i][j].color);
		ft_fprintf(1, "\n");
	}
	dblfree((void **)v);
	exit(0);
	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_mouse_hook(m.win, &mouse_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	close(fd);
	(void)v;
	return (EXIT_SUCCESS);
}
