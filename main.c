/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/10 09:35:40 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_fdf.h"

/* TODO:	Input error management */
/* 			Read the map from input */
int	main(void)
{
	t_vertex	**v;
	t_mlx		m;
	int			fd;
	
	char	*test_file = "maps/elem2.fdf";
	// char	*test_file = "maps/elem-col.fdf";
	// char	*test_file = "maps/pyramide.fdf";
	// char	*test_file = "maps/pylone.fdf";
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
	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_mouse_hook(m.win, &mouse_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	close(fd);
	return (EXIT_SUCCESS);
}
