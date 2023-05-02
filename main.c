/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/02 12:20:55 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"ft_fdf.h"

// TODO:
// Gradient color from a to b function

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
			put_vertex(&v[i][j], m); // TODO: instead of printing, just change values
			ft_fprintf(1, "v[i][j].x: %d\t", v[i][j].x);
			ft_fprintf(1, "v[i][j].y: %d\n", v[i][j].y);
			j++;
		}
		// bresenham(v[i][j], v[i + 1][j], m);
		// bresenham(v[i + 1][j], v[i + 1][j + 1], m);
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (i < v[i]->size_y - 1)
	{
		while (j < v[i]->size_x - 1)
		{
			bresenham(v[i][j], v[i][j + 1], m);
			bresenham(v[i][j], v[i + 1][j], m);
			j++;
		}
		// bresenham(v[i][j], v[i + 1][j], m);
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
	
	// char	*test_file = "maps/42.fdf";
	// char	*test_file = "maps/elem-col.fdf";
	char	*test_file = "maps/pyramide.fdf";
	// char	*test_file = "maps/100-6.fdf";
	// char	*test_file = "maps/t2.fdf";
	// char	*test_file = "maps/julia.fdf";
	// char	*test_file = "maps/mars.fdf";
	// char	*test_file = "maps/pentenegpos.fdf";
	
	fd = open(test_file, O_RDONLY);
	if (fd == -1)
		perror("Error"); // exit on error, make a function
	init_mlx(&m);
	v = read_map(fd, count_rows(test_file));
	print_lines(v, m);
	freemap(v);
	// mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_mouse_hook(m.win, &mouse_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	close(fd);
	return (EXIT_SUCCESS);
}
