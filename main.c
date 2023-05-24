/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/24 12:14:12 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_fdf.h"

/*
*Error management. List of codes:
**	0 = Wrong number of arguments
**	1 = Error upon opening file
**	2 = Error on memory allocation
**	3 = Wrong fdf format
*/
int	error_exit(int code)
{
	if (code == 0)
		ft_fprintf(2, "\e[1;31mUsage: ./fdf map.fdf. Exiting.\e[m\n");
	if (code == 1)
		ft_fprintf(2, "\e[1;31mCould not read the file. Exiting.\e[m\n");
	if (code == 2)
		ft_fprintf(2, "\e[1;31mError on malloc operation. Exiting.\e[m\n");
	if (code == 3)
		ft_fprintf(2, "\e[1;31mFound wrong line length. Exiting.\e[m\n");
	return (EXIT_FAILURE);
}

/*
* TODO:
**  	Implement perspective projection
**		Adapt to Norm (static functions)
*/
int	main(int argc, char **argv)
{
	t_mlx		m;
	int			fd;

	if (argc != 2)
		return (error_exit(0));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (error_exit(1));
	m.v = read_map(fd, count_rows(argv[1]));
	init_mlx(&m);
	// xyztoperspective(&m);
	// center_map(&m);
	xyztoiso(m.v);
	frame_map(m.v);
	print_lines(m.v, m);
	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_mouse_hook(m.win, &mouse_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	close(fd);
	freemap(m.v);
	return (EXIT_SUCCESS);
}
