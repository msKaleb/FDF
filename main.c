/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/28 17:44:54 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"ft_fdf.h"
#include<fcntl.h>

// TODO:
// Gradient color from a to b function


/*Get rid of 'y' argument */
t_vertex	*get_coords(char **line, int y, int rows)
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
		v[i].y = y * ((DEFAULT_Y / 3) / rows);
		v[i].x = (DEFAULT_X / 2) + i * (DEFAULT_X / (xlen * 2));
		v[i].y = y * ((DEFAULT_Y / 2) / rows);
		v[i].z = ft_atoi(line[i]) * 2; // TODO: Find a valid multiplier (depending on the max z value)
		if (ft_strchr(line[i], ',')) // TODO: implement this if-else inside get_color()
			v[i].color = get_color(ft_strchr(line[i], ',') + 1); // TODO: get lower case and incomplete numbers (0xff), to work
		else
			v[i].color = DEFAULT_COLOR;
		v[i].size_x = xlen;
		i++;
	}
	return (v);
}


int	close_mlx(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->img);
	mlx_destroy_window(m->mlx, m->win);		
	// mlx_destroy_display(m->mlx);
	free(m->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int key_code, t_mlx *m)
{
	// ft_fprintf(1, "%s\n", change_base((unsigned long long)key_code, 'x'));
	if (key_code == 0x35) // 0xff1b in Linux
		close_mlx(m);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *m)
{
	(void)m;
	ft_fprintf(1, "%d - %d - %d\n", button, x, y);
	return (0);
}



/* find the screen xy with trig, should I use mlx_pixel_put? */
/* -try Joe Iddon solution- */
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
	// ft_fprintf(1, "x: %d y: %d - scr_x: %d ", v.x, v.y, scr_x);
	mlx_pixel_put(m.mlx, m.win, scr_x, scr_y, v.color);
	
	// offset = (v.y * m.sl) + (v.x * (m.bpp / 8)); // how is it calculated?
	// offset = (scr_y * m.sl + scr_x * (m.bpp / 8)); // do I need this?
	// ptr = m.addr + offset;
	// // for making each vertex of 4 pixels...
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
	v = malloc(sizeof(t_vertex *) * (rows + 1));
	while((line = get_next_line(fd)) != NULL) // TODO: make a function to read the map
	{
		linexyz = ft_split(line, ' ');
		v[i] = get_coords(linexyz, i, rows);
		i++;
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
	// char	*test_file = "maps/elem-col.fdf";
	// char	*test_file = "maps/pyramide.fdf";
	char	*test_file = "maps/elem2.fdf";
	// char	*test_file = "maps/julia.fdf";
	// char	*test_file = "maps/basictest.fdf";
	
	int	rows = count_rows(test_file);
	// ft_fprintf(1, "rows: %d\n", rows);
	fd = open(test_file, O_RDONLY);
	if (fd == -1)
		perror("Error"); // exit on error, make a function
	init_mlx(&m);
	v = read_map(fd, rows);
	// loop for putting vertices using **v structure
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < v[i]->size_x - 1; j++){
			// put_vertex(v[i][j], m);
			bresenham(v[i][j], v[i][j + 1], m);
		}
			// dda_line(v[i][j], v[i][j + 1], &m);
		// ft_fprintf(1, "\n");
		}
	freemap(v);
	// mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_mouse_hook(m.win, &mouse_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	close(fd);
	(void)v;
	return (EXIT_SUCCESS);
}
