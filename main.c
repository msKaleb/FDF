/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/26 10:18:18 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mlx_linux/mlx.h" // For Linux
// #include"mlx/mlx.h"
#include"ft_fdf.h"
#include"LibFT/libft.h"
#include<fcntl.h>

// TODO:
// Gradient color from a to b function

/* t_vertex	*get_coords(char **line)
{
	t_vertex	*v;
	int		i;
	int		n;
	
	i = 0;
	while (line[i])
		i++;
	v = malloc(sizeof(v) * i);
	n = i;
	i = -1;
	while(++i < n)
	{
		v[i].x = 20 + i * (640 / n);
		v[i].z = ft_atoi(line[i]);
		ft_fprintf(1, "%d-", v[i].z);
	}
	return (v);
} */

int	get_color(char *str)
{
	int		color;
	
	color = ft_atoi_base(str + 2, "0123456789ABCDEF");
	return (color);
}

/* Change the value of x and y, maybe with macros */
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
		v[i].y = y * ((DEFAULT_Y / 3) / 10);	// TODO: change 10 for number of lines in the map
		v[i].z = ft_atoi(line[i]) * 5; // TODO: Find a valid multiplier (depending on the max z value)
		if (ft_strchr(line[i], ','))
			v[i].color = get_color(ft_strchr(line[i], ',') + 1);
		else
			v[i].color = 0xFFFFFF;
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

/* 0xff1b = esc key */
int	key_hook(int key_code, t_mlx *m)
{
	ft_fprintf(1, "%s\n", change_base(key_code, 'x'));
	if (key_code == XK_Escape)
	{
		mlx_destroy_image(m->mlx, m->img);
		mlx_destroy_window(m->mlx, m->win);		
		mlx_destroy_display(m->mlx);
		free(m->mlx);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *m)
{
	(void)m;
	ft_fprintf(1, "%d - %d - %d\n", button, x, y);
	return (0);
}

/* find the screen xy with trig, should I use mlx_pixel_put? */
/* try Joe Iddon solution */
/* TRUE_ISO: 30º angle */
/* ISO: 26.57º angle */
void	put_vertex(t_vertex v, t_mlx m)
{
	// char	*ptr;
	// int		offset;
	int		scr_x;
	int		scr_y;
	
	scr_x = (v.x - v.y) * cos(TRUE_ISO);
	scr_y = -v.z + (v.x + v.y) * sin(TRUE_ISO);
	mlx_pixel_put(m.mlx, m.win, scr_x, scr_y, v.color); // Almost!!!
	
	// offset = (v.y * m.sl + v.x * (m.bpp / 8)); // do I need this?
	// offset = (scr_y * m.sl + scr_x * (m.bpp / 8)); // do I need this?
	// ptr = m.addr + offset;
	// for making each vertex of 4 pixels...
	// *(unsigned int*)ptr = v.color;
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

int	main(void)
{
	t_vertex	*v;
	t_mlx		m;
	char		**linexyz;
	int 		x = -1;
	int 		y = 0;
	
	char		*line;
	int			fd;
	// char	*test_file = "maps/42.fdf";
	char	*test_file = "maps/elem-col.fdf";
	
	init_mlx(&m);
	fd = open(test_file, O_RDONLY);
	if (fd == -1)
		perror("Error"); // exit on error, make a function
	while((line = get_next_line(fd)) != NULL) // TODO: make a function to read the map
	{
		linexyz = ft_split(line, ' ');
		v = get_coords(linexyz, y);
		while (linexyz[++x])
		{
			put_vertex(v[x], m);
			// ft_fprintf(1, "x: %d ", v[x].x);
			// if (line[x] != ' ')
			// 	mlx_pixel_put(m.mlx, m.win, x, y, 255);
			// else
			// 	mlx_pixel_put(m.mlx, m.win, x, y, 255255);
			// ft_fprintf(1, "it: %d - x: %d - str: %s\n", x, v[x].x, linexyz[x]);
			// ft_fprintf(1, "x: %d - y: %d - z: %d - color: %d\n", v[x].x, v[x].y, v[x].z, v[x].color);
		}
		// ft_fprintf(1, "\n");
		y++;
		x = -1;
		free(v);
		free(line);
		dblfree((void **)linexyz);
	}
	close(fd);
	// mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_mouse_hook(m.win, &mouse_hook, &m);
	mlx_loop(m.mlx);
	return (EXIT_SUCCESS);
}

/* int	main(void)
{
	t_mlx	m;
	
	char	*test_file = "maps/42.fdf";
	// int		bpp;
	// int		sl;
	// int		endian;
	void	*ptr;
	int		color = 0x00FF0000;
	t_vertex	*v;
	// char	c = 255;
	// ft_fprintf(1, "%d\n", 255 << 8);
	// exit(0);
	
	int		fd;
	char	*line;


	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, 640, 480, "Test");
	m.img = mlx_new_image(m.mlx, 640, 480);
	m.addr = mlx_get_data_addr(m.img, &m.bpp, &m.sl, &m.endian);

	ptr = m.addr;
	int x = -1;
	int y = 0;
	char **linexyz;
	ptr = &x;
	

	
	fd = open(test_file, O_RDONLY);
	if (fd == -1)
		perror("");
	while((line = get_next_line(fd)) != NULL)
	{
		linexyz = ft_split(line, ' ');
		v = get_coords(linexyz);
		
		while (linexyz[++x])
		{
			color = v[x].z + 0xffffff;
			mlx_pixel_put(m.mlx, m.win, v[x].x, y * (480 / 11), color);
			// ft_fprintf(1, "x: %d ", v[x].x);
			// if (line[x] != ' ')
			// 	mlx_pixel_put(m.mlx, m.win, x, y, 255);
			// else
			// 	mlx_pixel_put(m.mlx, m.win, x, y, 255255);

		}
		ft_fprintf(1, "\n");
		y++;
		x = -1;
		// free(v);
		// break;
		// line = get_next_line(fd);
	}
	
	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	// exit(0);
	

	
	ft_fprintf(1, "m.bpp: %d\n", m.bpp);
	ft_fprintf(1, "m.sl: %d\n", m.sl);
	close(fd);

	mlx_key_hook(m.win, &key_hook, &m);
	mlx_loop(m.mlx);
	
	for (int y = 0; y < 480; y++){
		for(int x = 0; x < m.sl; x++){
			ptr = m.addr + (y * m.sl + x * (m.bpp / 8));
			*(unsigned int*)ptr = color + y;
		}
	}

	
} */
