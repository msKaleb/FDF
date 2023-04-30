/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/30 13:14:54 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"ft_fdf.h"

// TODO:
// Gradient color from a to b function

/* find the screen xy with trig, should I use mlx_pixel_put? */
/* -try Joe Iddon solution- */
/* TRUE_ISO: 30º angle */
/* ISO: 26.57º angle */
/* change or create a new array with the new values */
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

void	print_lines(t_vertex **v, t_mlx m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < v[i]->size_y - 1)
	{
		while (j < v[i]->size_x - 1)
		{
			// ft_fprintf(1, "i: %d, j: %d\n", i, j);
			bresenham(v[i][j], v[i][j + 1], m);
			bresenham(v[i][j], v[i + 1][j], m);
			j++;
		}
		bresenham(v[i][j], v[i + 1][j], m);
		// bresenham(v[i + 1][j], v[i + 1][j + 1], m);
		j = 0;
		i++;
	}
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
	char	*test_file = "maps/pyramide.fdf";
	// char	*test_file = "maps/elem2.fdf";
	// char	*test_file = "maps/julia.fdf";
	// char	*test_file = "maps/basictest.fdf";
	
	int	rows = count_rows(test_file);
	// ft_fprintf(1, "rows: %d\n", rows);
	fd = open(test_file, O_RDONLY);
	if (fd == -1)
		perror("Error"); // exit on error, make a function
	init_mlx(&m);
	v = read_map(fd, rows);
	print_lines(v, m);
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
